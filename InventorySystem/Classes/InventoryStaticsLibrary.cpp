// © 2025 Skydream Interactive. All rights reserved. ABYSSWHISPER™ is a trademark of Skydream Interactive.
// Unreal® Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere. All other trademarks are the property of their respective owners.

#include "Systems/InventorySystem/Classes/InventoryStaticsLibrary.h"

bool UInventoryStaticsLibrary::IsSlotValid(FSlotSignature SlotSignature)
{
	return SlotSignature.ItemClass != nullptr && SlotSignature.ItemClass.IsValid();
}

FText UInventoryStaticsLibrary::GetItemName(TSoftObjectPtr<UItemData> ItemDataAsset)
{
	if (ItemDataAsset)
	{
		return ItemDataAsset->ItemName;
	}
	return FText::GetEmpty();
}

FText UInventoryStaticsLibrary::GetItemDescription(TSoftObjectPtr<UItemData> ItemDataAsset)
{
	if (ItemDataAsset)
	{
		return ItemDataAsset->ItemDescription;
	}
	return FText::GetEmpty();
}

EItemType UInventoryStaticsLibrary::GetItemType(TSoftObjectPtr<UItemData> ItemDataAsset)
{
	if (ItemDataAsset)
	{
		return ItemDataAsset->ItemType;
	}
	return EItemType::Miscellaneous;
}

FIntPoint UInventoryStaticsLibrary::GetItemDimension(TSoftObjectPtr<UItemData> ItemDataAsset)
{
	if (ItemDataAsset)
	{
		return ItemDataAsset->ItemDimension;
	}
	return FIntPoint(0, 0);
}

TSoftObjectPtr<UTexture2D> UInventoryStaticsLibrary::GetItemTexture(TSoftObjectPtr<UItemData> ItemDataAsset)
{
	if (ItemDataAsset)
	{
		return ItemDataAsset->ItemTexture;
	}
	return nullptr;
}

TSoftObjectPtr<UStaticMesh> UInventoryStaticsLibrary::GetItemStaticMesh(TSoftObjectPtr<UItemData> ItemDataAsset)
{
	if (ItemDataAsset)
	{
		ItemDataAsset->ItemMesh;
	}
	return nullptr;
}

bool UInventoryStaticsLibrary::GetItemIsUsable(TSoftObjectPtr<UItemData> ItemDataAsset)
{
	if (ItemDataAsset)
	{
		ItemDataAsset->bIsUsable;
	}
	return false;
}

bool UInventoryStaticsLibrary::GetItemIsStackble(TSoftObjectPtr<UItemData> ItemDataAsset)
{
	if (ItemDataAsset)
	{
		ItemDataAsset->bIsStackble;
	}
	return false;
}

int32 UInventoryStaticsLibrary::GetItemMaxStackSize(TSoftObjectPtr<UItemData> ItemDataAsset)
{
	if (ItemDataAsset)
	{
		ItemDataAsset->MaxStackSize;
	}
	return INDEX_NONE;
}

bool UInventoryStaticsLibrary::GetItemIsAllowQuickAccess(TSoftObjectPtr<UItemData> ItemDataAsset)
{
	if (ItemDataAsset)
	{
		return ItemDataAsset->bAllowQuickAccess;
	}
	return false;
}

TSoftObjectPtr<UTexture2D> UInventoryStaticsLibrary::GetItemQuickAccessTexture(TSoftObjectPtr<UItemData> ItemDataAsset)
{
	if (ItemDataAsset)
	{
		return ItemDataAsset->QuickAccessTexture;
	}
	return nullptr;
}

TSubclassOf<UConsumableBase> UInventoryStaticsLibrary::GetItemConsumableClass(TSoftObjectPtr<UItemData> ItemDataAsset)
{
	if (ItemDataAsset)
	{
		return ItemDataAsset->ConsumableClass;
	}
	return nullptr;
}

FName UInventoryStaticsLibrary::GetItemID(TSoftObjectPtr<UItemData> ItemDataAsset)
{
	if (ItemDataAsset)
	{
		return ItemDataAsset->ItemID;
	}
	return FName("None");
}