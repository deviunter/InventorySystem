// Copyright SPYTHOONA INTERACTIVE. All rights reserved. ABYSSWHISPER is a trademark of SPYTHOONA INTERACTIVE.
// Unreal Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere.All other trademarks are the property of their respective owners.

// Reflection Engine © 2026 SPYTHOONA INTERACTIVE.All Rights Reserved.
// This software and its source code are the intellectual property of SPYTHOONA INTERACTIVE.
// Unauthorized copying, modification, distribution, or use is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "Systems/InventorySystem/Enumerators/InventoryEnumetators.h"
#include "ResourceSignature.generated.h"

USTRUCT(BlueprintType)
struct FResourceSignature
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentAmmound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxAmmound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EResourceType ResourceType;
};