// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/InventorySystem/Classes/ContainerInventoryComponent.h"

UContainerInventoryComponent::UContainerInventoryComponent()
{
	InventoryType = EInventoryType::ContainerInventory;
	RowSize = 6;
	ColumnSize = 10;
}

bool UContainerInventoryComponent::InspectInventory()
{
	bIsContainerInspected = true;
	if (FMath::FRandRange(0.0f, 1.0f) < 0.5f) return false;
	TObjectPtr<ULootDataAsset> SelectedLoot = LootDataAssets[FMath::RandRange(0, LootDataAssets.Num() - 1)];
	for (FLootDropList LocalDrop : SelectedLoot->GetLootDropList())
	{
		if (LocalDrop.ChanceOfDrop >= FMath::FRandRange(0.0f, 1.0f)) AddItemAtClass(LocalDrop.Item, FMath::RandRange(LocalDrop.AmmoundMin, LocalDrop.AmmoundMax));
	}
	return true;
}

bool UContainerInventoryComponent::IsContainerInspected() const
{
	return bIsContainerInspected;
}

EItemRarity UContainerInventoryComponent::GetContainerRarity() const
{
	return ContainerRarity;
}
