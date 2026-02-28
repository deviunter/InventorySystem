// Copyright SPYTHOONA INTERACTIVE. All rights reserved. ABYSSWHISPER is a trademark of SPYTHOONA INTERACTIVE.
// Unreal Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere.All other trademarks are the property of their respective owners.page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Systems/InventorySystem/Classes/InventoryComponent.h"
#include "Systems/InventorySystem/DataAssets/LootDataAsset.h"
#include "StashInventoryComponent.generated.h"

UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class ABYSSWHISPER_API UStashInventoryComponent : public UInventoryComponent
{
	GENERATED_BODY()

public:

	UStashInventoryComponent();

	UPROPERTY(EditAnywhere)
	TObjectPtr<ULootDataAsset> LootInfo;

	UFUNCTION(BlueprintCallable, Category = "Stash Optimization")
	void OnPlayerIsNear();
	
};
