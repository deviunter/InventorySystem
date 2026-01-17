// © 2025 Skydream Interactive. All rights reserved. ABYSSWHISPER™ is a trademark of Skydream Interactive.
// Unreal® Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere. All other trademarks are the property of their respective owners.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Systems/InventorySystem/Enumerators/InventoryEnumetators.h"
#include "Systems/InventorySystem/Structures/Tile.h"
#include "Systems/InventorySystem/Classes/ConsumableBase.h"
#include "ItemData.generated.h"

UCLASS()
class ABYSSWHISPER_API UItemData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	FText ItemName;

	UPROPERTY(EditDefaultsOnly, meta = (MultiLine = "true"))
	FText ItemDescription;

	UPROPERTY(EditDefaultsOnly)
	EItemType ItemType;

	UPROPERTY(EditDefaultsOnly)
	FIntPoint ItemDimension;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UTexture2D> ItemTexture;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UStaticMesh> ItemMesh;

	UPROPERTY(EditDefaultsOnly)
	bool bIsUsable;

	UPROPERTY(EditDefaultsOnly)
	bool bIsStackble;

	UPROPERTY(EditDefaultsOnly)
	int32 MaxStackSize;

	UPROPERTY(EditDefaultsOnly)
	bool bAllowQuickAccess;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UTexture2D> QuickAccessTexture;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UConsumableBase> ConsumableClass;

	UPROPERTY(EditDefaultsOnly)
	FName ItemID;
};
