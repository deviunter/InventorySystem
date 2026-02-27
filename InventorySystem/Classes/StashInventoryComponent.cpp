// Copyright SPYTHOONA INTERACTIVE. All rights reserved. ABYSSWHISPER is a trademark of SPYTHOONA INTERACTIVE.
// Unreal Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere.All other trademarks are the property of their respective owners.

#include "Systems/InventorySystem/Classes/StashInventoryComponent.h"
#include "Systems/InventorySystem/Structures/LootDropList.h"

UStashInventoryComponent::UStashInventoryComponent()
{
	InventoryType = EInventoryType::LootboxInventory;
	RowSize = 6;
	ColumnSize = 10;
}

void UStashInventoryComponent::OnPlayerIsNear()
{
	if (!IsValid(LootInfo)) return;
	for (FLootDropList LocalDrop : LootInfo->GetLootDropList())
	{
		if (LocalDrop.ChanceOfDrop >= FMath::FRandRange(0.0f, 1.0f))
		{
			AddItemAtClass(LocalDrop.Item, FMath::RandRange(LocalDrop.AmmoundMin, LocalDrop.AmmoundMax));
		}
	}
	LootInfo = nullptr;
}
