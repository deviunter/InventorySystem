// Copyright SPYTHOONA INTERACTIVE. All rights reserved. ABYSSWHISPER is a trademark of SPYTHOONA INTERACTIVE.
// Unreal Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere.All other trademarks are the property of their respective owners.

// Reflection Engine Copyrignt 2026 SPYTHOONA INTERACTIVE.All Rights Reserved.
// This software and its source code are the intellectual property of SPYTHOONA INTERACTIVE.
// Unauthorized copying, modification, distribution, or use is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "Systems/InventorySystem/Classes/ItemBase.h"
#include "Systems/InventorySystem/Structures/Tile.h"
#include "Systems/InventorySystem/Structures/KeyDataSignature.h"
#include "Systems/InventorySystem/Structures/ResourceSignature.h"
#include "InventorySave.generated.h"

USTRUCT(BlueprintType)
struct FItemSaveInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UItemBase> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemAmmound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemTopLeftIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemTile ItemTile;
};

USTRUCT(BlueprintType)
struct FSupportInventoryInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UItemBase> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SupportInventoryIndex;
};

USTRUCT(BlueprintType)
struct FInventorySave
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FItemSaveInfo> ItemSaveInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ColumnSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RowSize;
};

USTRUCT(BlueprintType)
struct FPlayerInventorySaveSignature
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FInventorySave InventoryInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FResourceSignature> ResourcesInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FKeyDataSignature> KeyDataItemsInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSupportInventoryInfo> QuickAccessSlotsInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSupportInventoryInfo> CharmInventorySlotsInfo;
};