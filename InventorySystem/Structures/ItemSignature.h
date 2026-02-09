// Copyright SPYTHOONA INTERACTIVE.All rights reserved.ABYSSWHISPER is a trademark of SPYTHOONA INTERACTIVE.
// Unreal Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere.All other trademarks are the property of their respective owners.

// Reflection Engine © 2026 SPYTHOONA INTERACTIVE.All Rights Reserved.
// This software and its source code are the intellectual property of SPYTHOONA INTERACTIVE.
// Unauthorized copying, modification, distribution, or use is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "Systems/InventorySystem/Enumerators/InventoryEnumetators.h"
#include "Systems/InventorySystem/Structures/Tile.h"
#include "ItemSignature.generated.h"

USTRUCT(BlueprintType)
struct FItemSignature
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = "true"))
	FText ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntPoint ItemDimension;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> ItemTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsUsable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsStackble;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxStackSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAllowQuickAccess;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> QuickAccessTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemID;
};