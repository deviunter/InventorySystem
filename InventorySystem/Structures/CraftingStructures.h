// Copyright SPYTHOONA INTERACTIVE. All rights reserved. ABYSSWHISPER is a trademark of SPYTHOONA INTERACTIVE.
// Unreal Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere.All other trademarks are the property of their respective owners.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Systems/InventorySystem/Enumerators/InventoryEnumetators.h"
#include "Systems/InventorySystem/Classes/ItemBase.h"
#include "CraftingStructures.generated.h"

USTRUCT(BlueprintType)
struct FResourceCost
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EResourceType ResourceType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ResourceCost;
};

USTRUCT(BlueprintType)
struct FCraftingRecipe : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = "true"))
	FText ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FResourceCost> NecessaryResources;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UItemBase> ReceivedItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ReceivedAmmound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName KeyDataRecipeID;

};