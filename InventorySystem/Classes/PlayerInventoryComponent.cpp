// Copyright SPYTHOONA INTERACTIVE. All rights reserved. ABYSSWHISPER is a trademark of SPYTHOONA INTERACTIVE.
// Unreal Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere.All other trademarks are the property of their respective owners.

// Reflection Engine © 2026 SPYTHOONA INTERACTIVE.All Rights Reserved.
// This software and its source code are the intellectual property of SPYTHOONA INTERACTIVE.
// Unauthorized copying, modification, distribution, or use is strictly prohibited.

#include "Systems/InventorySystem/Classes/PlayerInventoryComponent.h"
#include "Core/Interfaces/HeadUpInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Character.h"
#include "Systems/InventorySystem/Classes/Items/Charms/CharmItemBase.h"

UPlayerInventoryComponent::UPlayerInventoryComponent()
{
	// RESOURCE LIST MAX AMMOUND SETUP
	WoodResourceMaxAmount = 20;
	MetalResourceMaxAmount = 25;
	ElectricalResourceMaxAmount = 15;
	ChemicalResourceMaxAmount = 30;
	BioResourceMaxAmount = 35;

	// RESOURCE LIST SETUP
	ResourceList.Empty();
	ResourceList.Add(FResourceSignature(0, WoodResourceMaxAmount, EResourceType::WoodResource));
	ResourceList.Add(FResourceSignature(0, MetalResourceMaxAmount, EResourceType::MetalResource));
	ResourceList.Add(FResourceSignature(0, ElectricalResourceMaxAmount, EResourceType::ElectricalResource));
	ResourceList.Add(FResourceSignature(0, ChemicalResourceMaxAmount, EResourceType::ChemicalResource));
	ResourceList.Add(FResourceSignature(0, BioResourceMaxAmount, EResourceType::BioResource));

	// KEY DATA LIST SETUP
	KeyDataList.Empty();

	// CHARM INVENTORY SETUP
	CharmInventoryLength = 3;
	RefreshCharmInventory();

	// QUICK ACCESS SLOTS SETUP
	QuickAccessSlots.SetNum(12);

	// CLASS SETUP
	InventoryType = EInventoryType::PlayerInventory;
}

void UPlayerInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	GetDisplayReference();
}

EResourceAddType UPlayerInventoryComponent::AddResouceAtType(EResourceType ResourceType, int32 AddAmmound)
{
	for (int32 i = 0; i < ResourceList.Num(); i++)
	{
		if (ResourceList[i].ResourceType == ResourceType)
		{
			if (ResourceList[i].CurrentAmmound + AddAmmound <= ResourceList[i].MaxAmmound)
			{
				ResourceList[i].CurrentAmmound += AddAmmound;
				ResourceNotification(ResourceType, AddAmmound);
				return EResourceAddType::Success;
			}
			else
			{
				ResourceList[i].CurrentAmmound = ResourceList[i].MaxAmmound;
				ResourceNotification(ResourceType, AddAmmound);
				return EResourceAddType::Partition;
			}
		}
	}
	return EResourceAddType::Fail;
}

FResourceSignature UPlayerInventoryComponent::GetResourceAtType(EResourceType ResourceType)
{
	for (int32 i = 0; i < ResourceList.Num(); i++)
	{
		if (ResourceList[i].ResourceType == ResourceType)
		{
			return ResourceList[i];
		}
	}
	return FResourceSignature();
}

bool UPlayerInventoryComponent::RemoveResourceAtType(EResourceType ResourceType, int32 RemoveAmmound)
{
	for (int32 i = 0; i < ResourceList.Num(); i++)
	{
		if (ResourceList[i].ResourceType == ResourceType)
		{
			if (ResourceList[i].CurrentAmmound > RemoveAmmound)
			{
				ResourceList[i].CurrentAmmound -= RemoveAmmound;
				return true;
			}
			else
			{
				ResourceList[i].CurrentAmmound = 0;
				return true;
			}
		}
	}
	return false;
}

TArray<FResourceSignature> UPlayerInventoryComponent::GetAllResources() const
{
	return ResourceList;
}

bool UPlayerInventoryComponent::AddKeyDataAtID(FName KeyDataID)
{
	UDataTable* KeyData = LoadObject<UDataTable>(nullptr, TEXT("/Game/SD/Systems/InventorySystem/DataTables/KeyDataItems"));
	if (!KeyData) return false;
	if (!KeyData->FindRow<FKeyDataSignature>(KeyDataID, TEXT(""), true)) return false;
	FKeyDataSignature* LocalKeyDataPtr = KeyData->FindRow<FKeyDataSignature>(KeyDataID, TEXT(""), true);
	FKeyDataSignature LocalKeyData = *LocalKeyDataPtr;
	AddKeyDataAtStructure(LocalKeyData);
	return true;
}

bool UPlayerInventoryComponent::AddKeyDataAtStructure(FKeyDataSignature KeyDataSignature)
{
	if (!IsKeyDataContains(KeyDataSignature.KeyDataID))
	{
		KeyDataList.Add(KeyDataSignature);
		KeyDataNotification(KeyDataSignature);
		return true;
	}
	else
	{
		return false;
	}
}

bool UPlayerInventoryComponent::SetKeyDataIsUsed(FName KeyDataID, bool NewIsUsed)
{
	for (int32 i = 0; i < KeyDataList.Num(); i++)
	{
		if (KeyDataList[i].KeyDataID == KeyDataID)
		{
			KeyDataList[i].bIsUsed = NewIsUsed;
			return true;
		}
	}
	return false;
}

bool UPlayerInventoryComponent::RemoveKeyDataAtID(FName KeyDataID)
{
	for (int32 i = 0; i < KeyDataList.Num(); i++)
	{
		if (KeyDataList[i].KeyDataID == KeyDataID)
		{
			KeyDataList.RemoveAt(i);
			return true;
		}
	}
	return false;
}

FKeyDataSignature UPlayerInventoryComponent::GetKeyDataAtID(FName KeyDataID)
{
	for (int32 i = 0; i < KeyDataList.Num(); i++)
	{
		if (KeyDataList[i].KeyDataID == KeyDataID)
		{
			return KeyDataList[i];
		}
	}
	return FKeyDataSignature();
}

TArray<FKeyDataSignature> UPlayerInventoryComponent::GetKeyDataCollected() const
{
	return KeyDataList;
}

bool UPlayerInventoryComponent::IsKeyDataContains(FName KeyDataID)
{
	for (int32 i = 0; i < KeyDataList.Num(); i++)
	{
		if (KeyDataList[i].KeyDataID == KeyDataID)
		{
			return true;
		}
	}
	return false;
}

bool UPlayerInventoryComponent::AddCharmItem(UItemBase* ItemToAdd)
{
	if (ItemToAdd->GetItemSignature().ItemType != EItemType::Charms) return false;
	if (!Cast<UCharmItemBase>(ItemToAdd)) return false;
	for (int32 i = 0; i < CharmsList.Num(); i++)
	{
		if (IsCharmSlotEmpty(i))
		{
			Cast<UCharmItemBase>(ItemToAdd)->CharmAdded();
			AddCharmItemToSlot(ItemToAdd, i);
			return true;
		}
	}
	return false;
}

bool UPlayerInventoryComponent::AddCharmItemToSlot(UItemBase* ItemToAdd, int32 SlotIndex)
{
	if (ItemToAdd->GetItemSignature().ItemType != EItemType::Charms) return false;
	if (!Cast<UCharmItemBase>(ItemToAdd)) return false;
	if (!IsCharmSlotEmpty(SlotIndex)) return false;
	CharmsList[SlotIndex] = ItemToAdd;
	Cast<UCharmItemBase>(ItemToAdd)->CharmAdded();
	return true;
}

bool UPlayerInventoryComponent::RemoveCharmItemAtIndex(int32 SlotIndex, bool DestroyItem)
{
	if (IsCharmSlotEmpty(SlotIndex)) return false;
	if (DestroyItem)
	{
		CharmsList[SlotIndex]->MarkAsGarbage();
	}
	if (!Cast<UCharmItemBase>(CharmsList[SlotIndex])) return false;
	Cast<UCharmItemBase>(CharmsList[SlotIndex])->CharmRemoved();
	CharmsList[SlotIndex] = nullptr;
	return true;
}

TArray<UItemBase*> UPlayerInventoryComponent::GetCharmItems() const
{
	return CharmsList;
}

UItemBase* UPlayerInventoryComponent::GetCharmItemAtIndex(int32 ItemIndex) const
{
	if (IsCharmSlotEmpty(ItemIndex))
	{
		return nullptr;
	}
	else
	{
		return CharmsList[ItemIndex];
	}
}

bool UPlayerInventoryComponent::IsCharmSlotEmpty(int32 SlotIndex) const
{
	if (IsValid(CharmsList[SlotIndex]))
	{
		return false;
	}
	else
	{
		return true;
	}
}

void UPlayerInventoryComponent::RefreshCharmInventory()
{
	CharmsList.SetNum(CharmInventoryLength);
}

UItemBase* UPlayerInventoryComponent::GetQuickAccessSlotAtIndex(int32 SlotIndex)
{
	if (!QuickAccessSlots.IsValidIndex(SlotIndex)) return nullptr;
	if (IsValid(QuickAccessSlots[SlotIndex])) return QuickAccessSlots[SlotIndex];
	return nullptr;
}

int32 UPlayerInventoryComponent::CheckEqualsWithQuickAccess(UItemBase* ItemToCheck)
{
	for (int32 i = 0; i < QuickAccessSlots.Num(); i++)
	{
		if (ItemToCheck->GetClass() == QuickAccessSlots[i]->GetClass())
		{
			return i;
		}
	}
	return INDEX_NONE;
}

bool UPlayerInventoryComponent::SetQuickAccessSlot(UItemBase* ItemToAdd, int32 Index)
{
	if (!IsValid(ItemToAdd)) return false;
	if (!QuickAccessSlots.IsValidIndex(Index)) return false;
	if (ItemToAdd->GetClass() == QuickAccessSlots[Index]->GetClass()) return false;
	for (int32 i = 0; i < QuickAccessSlots.Num(); i++)
	{
		if (ItemToAdd->GetClass() == QuickAccessSlots[i]->GetClass())
		{
			QuickAccessSlots[i] = nullptr;
			break;
		}
	}
	QuickAccessSlots[Index] = ItemToAdd;
	return true;
}

FPlayerInventorySaveSignature UPlayerInventoryComponent::GetPlayerInventorySaveData()
{
	FPlayerInventorySaveSignature LocalSave;
	TArray<FSupportInventoryInfo> CharmInfo;
	TArray<FSupportInventoryInfo> QuickAccessInfo;
	for (int32 i = 0; i < CharmsList.Num(); i++)
	{
		if (IsValid(CharmsList[i]))
		{
			FSupportInventoryInfo LocalItem;
			LocalItem.ItemClass = CharmsList[i]->GetClass();
			LocalItem.SupportInventoryIndex = i;
			CharmInfo.Add(LocalItem);
		}
	}
	for (int32 i = 0; i < QuickAccessSlots.Num(); i++)
	{
		if (IsValid(QuickAccessSlots[i]))
		{
			FSupportInventoryInfo LocalQAItem;
			LocalQAItem.ItemClass = QuickAccessSlots[i]->GetClass();
			LocalQAItem.SupportInventoryIndex = i;
			QuickAccessInfo.Add(LocalQAItem);
		}
	}
	LocalSave.ItemSlotsInfo = GetInventorySaveData();
	LocalSave.Resources = ResourceList;
	LocalSave.KeyDataItemsInfo = KeyDataList;
	LocalSave.CharmInventorySlots = CharmInfo;
	LocalSave.QuickAccessSlots = QuickAccessInfo;
	return LocalSave;
}

void UPlayerInventoryComponent::SetPlayerInventoryLoadData(FPlayerInventorySaveSignature InventorySaveData)
{
	SetInventoryLoadData(InventorySaveData.ItemSlotsInfo);
	ResourceList = InventorySaveData.Resources;
	KeyDataList = InventorySaveData.KeyDataItemsInfo;
	for (int32 i = 0; i < InventorySaveData.QuickAccessSlots.Num(); i++)
	{
		if (IsValid(GetItemAtClass(InventorySaveData.QuickAccessSlots[i].ItemClass)))
		{
			SetQuickAccessSlot(GetItemAtClass(InventorySaveData.QuickAccessSlots[i].ItemClass), i);
		}
	}
	for (int32 i = 0; i < InventorySaveData.CharmInventorySlots.Num(); i++)
	{
		UItemBase* LocalCharm = NewObject<UItemBase>(this, InventorySaveData.CharmInventorySlots[i].ItemClass);
		AddCharmItemToSlot(LocalCharm, i);
	}
}

void UPlayerInventoryComponent::AddItemNotification(UItemBase* AddedItem, EInventoryAddingType ItemState)
{
	Super::AddItemNotification(AddedItem, ItemState);
	if (ItemState == EInventoryAddingType::NotAdded)
	{
		IHeadUpInterface::Execute_InventoryOverloaded((UObject*)PlayerDisplay);
	}
	else
	{
		IHeadUpInterface::Execute_ItemAdded((UObject*)PlayerDisplay, AddedItem->GetItemSignature());
	}
}

void UPlayerInventoryComponent::ResourceNotification(EResourceType Resource, int32 AddedAmount)
{
	IHeadUpInterface::Execute_ResourceAdded((UObject*)PlayerDisplay, Resource, AddedAmount);
}

void UPlayerInventoryComponent::KeyDataNotification(FKeyDataSignature KeyData)
{
	IHeadUpInterface::Execute_KeyDataItemAdded((UObject*)PlayerDisplay, KeyData);
}

void UPlayerInventoryComponent::GetDisplayReference()
{
	if (!Cast<ACharacter>(GetOwner())) return;
	if (!Cast<APlayerController>(Cast<ACharacter>(GetOwner())->GetController())) return;
	PlayerDisplay = Cast<APlayerController>(Cast<ACharacter>(GetOwner())->GetController())->GetHUD();
}