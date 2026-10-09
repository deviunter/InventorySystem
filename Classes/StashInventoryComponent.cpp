// Copyright SPYTHOONA INTERACTIVE. All rights reserved. ABYSSWHISPER is a trademark of SPYTHOONA INTERACTIVE.
// Unreal Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere.All other trademarks are the property of their respective owners.

// Reflection Engine Copyrignt 2026 SPYTHOONA INTERACTIVE. All Rights Reserved.
// This software and its source code are the intellectual property of SPYTHOONA INTERACTIVE.
// Unauthorized copying, modification, distribution, or use is strictly prohibited.

#include "Systems/InventorySystem/Classes/StashInventoryComponent.h"
#include "Systems/InventorySystem/Structures/LootDropList.h"
#include "Core/Interfaces/ActorsInterface.h"

UStashInventoryComponent::UStashInventoryComponent()
{
	InventoryType = EInventoryType::LootboxInventory;
	RowSize = 6;
	ColumnSize = 10;
}

void UStashInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	if (!GetOwner()->GetClass()->ImplementsInterface(UActorsInterface::StaticClass())) return;
	InventoryName = IActorsInterface::Execute_GetActorName((UObject*)GetOwner());
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

bool UStashInventoryComponent::IsStashInspected() const
{
	return !IsValid(LootInfo);
}

FStashInventorySaveSignature UStashInventoryComponent::GetStashInventorySaveData() const
{
	FStashInventorySaveSignature LocalData;
	if (IsStashInspected())
	{
		LocalData.InventoryInfo = GetInventorySaveData();
		LocalData.LootInfo = nullptr;
		LocalData.StashType = LocalData.InventoryInfo.ItemSaveInfo.IsEmpty() ? EStashType::EmptyStash : EStashType::OpenedStash;
	}
	else
	{
		LocalData.LootInfo = LootInfo;
		LocalData.StashType = EStashType::FillStash;
	}
	return LocalData;
}

void UStashInventoryComponent::SetStashInventoryLoadData(FStashInventorySaveSignature InventorySaveData)
{
	InventoryName = InventorySaveData.InventoryName;
	switch (InventorySaveData.StashType)
	{
	case EStashType::EmptyStash:
		GetOwner()->Destroy();
		break;
	case EStashType::FillStash:
		LootInfo = InventorySaveData.LootInfo;
		ItemSlots.Empty();
		UpdateInventorySize();
		break;
	case EStashType::OpenedStash:
		LootInfo = nullptr;
		SetInventoryLoadData(InventorySaveData.InventoryInfo);
		break;
	}
}
