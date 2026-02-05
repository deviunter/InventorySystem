// © 2025 Skydream Interactive. All rights reserved. ABYSSWHISPER™ is a trademark of Skydream Interactive.
// Unreal® Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere. All other trademarks are the property of their respective owners.

// Reflection Engine © 2025 Deviunter & Skydream Interactive. All Rights Reserved. 
// This software and its source code are the intellectual property of Skydream Interactive.
// Unauthorized copying, modification, distribution, or use is strictly prohibited.

#include "Systems/InventorySystem/Classes/PlayerInventoryComponent.h"

UPlayerInventoryComponent::UPlayerInventoryComponent()
{
	// SET UP RESOURCE ARRAY TYPES MAX AMOUNT
	WoodResourceMaxAmount = 20;
	MetalResourceMaxAmount = 25;
	ElectricalResourceMaxAmount = 15;
	ChemicalResourceMaxAmount = 30;
	BioResourceMaxAmount = 35;

	// SET UP RESOURCE ARRAY
	ResourceList.Empty();
	ResourceList.Add(FResourceSignature(0, WoodResourceMaxAmount, EResourceType::WoodResource));
	ResourceList.Add(FResourceSignature(0, MetalResourceMaxAmount, EResourceType::MetalResource));
	ResourceList.Add(FResourceSignature(0, ElectricalResourceMaxAmount, EResourceType::ElectricalResource));
	ResourceList.Add(FResourceSignature(0, ChemicalResourceMaxAmount, EResourceType::ChemicalResource));
	ResourceList.Add(FResourceSignature(0, BioResourceMaxAmount, EResourceType::BioResource));

	// SET UP KEY DATA ARRAY
	KeyDataList.Empty();

	// SET UP CHARMS INVENTORY
	CharmInventoryLength = 3;
	RefreshCharmInventory();
}

EResourceAddType UPlayerInventoryComponent::AddResouceAtType(EResourceType ResourceType, int32 AddAmmound)
{
	for (int32 i = 0; i < ResourceList.Num(); i++)
	{
		if (ResourceList[i].ResourceType == ResourceType)
		{
			if (ResourceList[i].MaxAmmound + AddAmmound <= ResourceList[i].MaxAmmound)
			{
				ResourceList[i].CurrentAmmound += AddAmmound;
				return EResourceAddType::Success;
			}
			else
			{
				ResourceList[i].CurrentAmmound = ResourceList[i].MaxAmmound;
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
	for (int32 i = 0; i < CharmsList.Num(); i++)
	{
		if (IsCharmSlotEmpty(i))
		{
			AddCharmItemToSlot(ItemToAdd, i);
			return true;
		}
	}
	return false;
}

bool UPlayerInventoryComponent::AddCharmItemToSlot(UItemBase* ItemToAdd, int32 SlotIndex)
{
	if (ItemToAdd->GetItemSignature().ItemType != EItemType::Charms) return false;
	CharmsList[SlotIndex] = ItemToAdd;
	return true;
}

bool UPlayerInventoryComponent::RemoveCharmItemAtIndex(int32 SlotIndex, bool DestroyItem)
{
	if (IsCharmSlotEmpty(SlotIndex)) return false;
	if (DestroyItem)
	{
		CharmsList[SlotIndex]->MarkAsGarbage();
	}
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
