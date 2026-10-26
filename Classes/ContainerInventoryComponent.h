// Copyright SPYTHOONA INTERACTIVE. All rights reserved. ABYSSWHISPER is a trademark of SPYTHOONA INTERACTIVE.
// Unreal Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere.All other trademarks are the property of their respective owners.page of Project Settings.

// Reflection Engine Copyrignt 2026 SPYTHOONA INTERACTIVE.All Rights Reserved.
// This software and its source code are the intellectual property of SPYTHOONA INTERACTIVE.
// Unauthorized copying, modification, distribution, or use is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "Systems/InventorySystem/Classes/InventoryComponent.h"
#include "ContainerInventoryComponent.generated.h"

UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class ABYSSWHISPER_API UContainerInventoryComponent : public UInventoryComponent
{
	GENERATED_BODY()

public:

	UContainerInventoryComponent();

	UFUNCTION(BlueprintCallable)
	bool InspectInventory();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsContainerInspected() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	EItemRarity GetContainerRarity() const;
	
	UPROPERTY(EditAnywhere, Category = "Generation")
	TArray<TObjectPtr<ULootDataAsset>> LootDataAssets;

	UPROPERTY(EditAnywhere, Category = "Generation")
	EItemRarity ContainerRarity;

private:

	UPROPERTY()
	bool bIsContainerInspected;
};
