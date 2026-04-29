// Copyright SPYTHOONA INTERACTIVE. All rights reserved. ABYSSWHISPER is a trademark of SPYTHOONA INTERACTIVE.
// Unreal Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere.All other trademarks are the property of their respective owners.

// Reflection Engine Copyrignt 2026 SPYTHOONA INTERACTIVE.All Rights Reserved.
// This software and its source code are the intellectual property of SPYTHOONA INTERACTIVE.
// Unauthorized copying, modification, distribution, or use is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "Systems/InventorySystem/DataAssets/LootDataAsset.h"
#include "Systems/InventorySystem/Enumerators/InventoryEnumetators.h"
#include "Engine/DataTable.h"
#include "GeneratedLootDataAsset.generated.h"

UCLASS()
class ABYSSWHISPER_API UGeneratedLootDataAsset : public ULootDataAsset
{
	GENERATED_BODY()

public:

	UGeneratedLootDataAsset();	

protected:

	virtual TArray<FLootDropList> GetOptions() override;

	UPROPERTY(EditDefaultsOnly)
	int32 MaxItemsLength;

	UPROPERTY(EditDefaultsOnly)
	ELootGenerateRules GenerateRules;

	UPROPERTY(EditDefaultsOnly)
	TArray<EItemType> LootTypes;

	UPROPERTY(EditDefaultsOnly)
	TArray<EItemRarity> LootRarities;

private:

	UPROPERTY()
	TObjectPtr<UDataTable> LootItemsTable;
};
