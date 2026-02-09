// Copyright SPYTHOONA INTERACTIVE.All rights reserved.ABYSSWHISPER is a trademark of SPYTHOONA INTERACTIVE.
// Unreal Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere.All other trademarks are the property of their respective owners.

// Reflection Engine © 2026 SPYTHOONA INTERACTIVE.All Rights Reserved.
// This software and its source code are the intellectual property of SPYTHOONA INTERACTIVE.
// Unauthorized copying, modification, distribution, or use is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "KeyDataSignature.generated.h"

USTRUCT(BlueprintType)
struct FKeyDataSignature : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName KeyDataID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText KeyDataName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = "true"))
	FText KeyDataDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* KeyDataMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> KeyDataTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntPoint KeyDataDimension;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsUsed;
};