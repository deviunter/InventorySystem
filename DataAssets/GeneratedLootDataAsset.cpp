// Copyright SPYTHOONA INTERACTIVE. All rights reserved. ABYSSWHISPER is a trademark of SPYTHOONA INTERACTIVE.
// Unreal Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere.All other trademarks are the property of their respective owners.

// Reflection Engine Copyrignt 2026 SPYTHOONA INTERACTIVE.All Rights Reserved.
// This software and its source code are the intellectual property of SPYTHOONA INTERACTIVE.
// Unauthorized copying, modification, distribution, or use is strictly prohibited.

#include "Systems/InventorySystem/DataAssets/GeneratedLootDataAsset.h"

UGeneratedLootDataAsset::UGeneratedLootDataAsset()
{
	LootItemsTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/SD/Systems/InventorySystem/DataTables/LootInventoryItems.LootInventoryItems"));
}

TArray<FLootDropList> UGeneratedLootDataAsset::GetOptions()
{
	LootDropList.Empty();
	if (!IsValid(LootItemsTable)) return LootDropList;

	UE_LOG(LogTemp, Warning, TEXT("GenerateRules: %d"), (int32)GenerateRules);
	UE_LOG(LogTemp, Warning, TEXT("LootTypes count: %d"), LootTypes.Num());
	UE_LOG(LogTemp, Warning, TEXT("LootRarities count: %d"), LootRarities.Num());

	TArray<FName> RowNames = LootItemsTable->GetRowNames();
	TArray<FLootDropList> LootItems;
	for (FName LocalRow : RowNames)
	{
		FLootItemInfo* Row = LootItemsTable->FindRow<FLootItemInfo>(LocalRow, TEXT(""));

		UE_LOG(LogTemp, Warning, TEXT("Row: %s | ItemType: %d | Rarity: %d"),
			*LocalRow.ToString(), (int32)Row->ItemType, (int32)Row->ItemRarity);

		if (!Row) continue;
		FLootItemInfo LootInfo = *Row;
		switch (GenerateRules)
		{
		case ELootGenerateRules::ByItemType:
			for (EItemType ItemType : LootTypes)
			{
				if (LootInfo.ItemType == ItemType)
				{
					FLootDropList DropItem;
					DropItem.Item = LootInfo.ItemClass;
					DropItem.ChanceOfDrop = 1.0f;
					if (LootInfo.bIsItemStackable)
					{
						DropItem.AmmoundMin = 1;
						DropItem.AmmoundMax = FMath::RandRange(2, LootInfo.MaxStackSize);
						LootItems.Add(DropItem);
						break;
					}
					else
					{
						DropItem.AmmoundMin = 1;
						DropItem.AmmoundMax = 1;
						LootItems.Add(DropItem);
						break;
					}
				}
			}
			break;
		case ELootGenerateRules::ByRarity:
			for (EItemRarity ItemRarity : LootRarities)
			{
				if (LootInfo.ItemRarity == ItemRarity)
				{
					FLootDropList DropItem;
					DropItem.Item = LootInfo.ItemClass;
					DropItem.ChanceOfDrop = 1.0f;
					if (LootInfo.bIsItemStackable)
					{
						DropItem.AmmoundMin = 1;
						DropItem.AmmoundMax = FMath::RandRange(2, LootInfo.MaxStackSize);
						LootItems.Add(DropItem);
						break;
					}
					else
					{
						DropItem.AmmoundMin = 1;
						DropItem.AmmoundMax = 1;
						LootItems.Add(DropItem);
						break;
					}
				}
			}
			break;
		case ELootGenerateRules::Shuffle:
			FLootDropList DropItem;
			DropItem.Item = LootInfo.ItemClass;
			DropItem.ChanceOfDrop = 1.0f;
			if (LootInfo.bIsItemStackable)
			{
				DropItem.AmmoundMin = 1;
				DropItem.AmmoundMax = FMath::RandRange(2, LootInfo.MaxStackSize);
				LootItems.Add(DropItem);
				break;
			}
			else
			{
				DropItem.AmmoundMin = 1;
				DropItem.AmmoundMax = 1;
				LootItems.Add(DropItem);
				break;
			}
		}
	}
	int32 LastIndex = LootItems.Num() - 1;
	for (int32 i = LastIndex; i > 0; i--)
	{
		int32 RandomIndex = FMath::RandRange(0, i);
		LootItems.Swap(i, RandomIndex);
	}
	if (LootItems.Num() > MaxItemsLength) LootItems.SetNum(MaxItemsLength);
	return LootItems;
}
