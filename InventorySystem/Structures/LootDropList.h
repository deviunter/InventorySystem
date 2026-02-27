// Copyright SPYTHOONA INTERACTIVE. All rights reserved. ABYSSWHISPER is a trademark of SPYTHOONA INTERACTIVE.
// Unreal Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere.All other trademarks are the property of their respective owners.

// Reflection Engine © 2026 SPYTHOONA INTERACTIVE.All Rights Reserved.
// This software and its source code are the intellectual property of SPYTHOONA INTERACTIVE.
// Unauthorized copying, modification, distribution, or use is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "Systems/InventorySystem/Classes/ItemBase.h"
#include "LootDropList.generated.h"

USTRUCT(BlueprintType)
struct FLootDropList
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UItemBase> Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ChanceOfDrop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AmmoundMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AmmoundMax;
};

