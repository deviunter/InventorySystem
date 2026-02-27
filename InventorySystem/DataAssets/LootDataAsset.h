// Copyright SPYTHOONA INTERACTIVE. All rights reserved. ABYSSWHISPER is a trademark of SPYTHOONA INTERACTIVE.
// Unreal Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere.All other trademarks are the property of their respective owners.

// Reflection Engine © 2026 SPYTHOONA INTERACTIVE.All Rights Reserved.
// This software and its source code are the intellectual property of SPYTHOONA INTERACTIVE.
// Unauthorized copying, modification, distribution, or use is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Systems/InventorySystem/Structures/LootDropList.h"
#include "LootDataAsset.generated.h"

UCLASS()
class ABYSSWHISPER_API ULootDataAsset : public UDataAsset
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly)
	TArray<FLootDropList> LootDropList;

public:

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<FLootDropList> GetLootDropList();
	
};
