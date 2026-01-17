// © 2025 Skydream Interactive. All rights reserved. ABYSSWHISPER™ is a trademark of Skydream Interactive.
// Unreal® Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere. All other trademarks are the property of their respective owners.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Systems/InventorySystem/Structures/SlotSignature.h"
#include "Systems/InventorySystem/DataAssets/ItemData.h"
#include "Systems/InventorySystem/Enumerators/InventoryEnumetators.h"
#include "InventoryStaticsLibrary.generated.h"

/**
 * 
 */
UCLASS()
class ABYSSWHISPER_API UInventoryStaticsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Validation")
	static bool IsSlotValid(FSlotSignature SlotSignature);

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Item")
	static FText GetItemName(TSoftObjectPtr<UItemData> ItemDataAsset);

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Item")
	static FText GetItemDescription(TSoftObjectPtr<UItemData> ItemDataAsset);

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Item")
	static EItemType GetItemType(TSoftObjectPtr<UItemData> ItemDataAsset);

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Item")
	static FIntPoint GetItemDimension(TSoftObjectPtr<UItemData> ItemDataAsset);

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Item")
	static TSoftObjectPtr<UTexture2D> GetItemTexture(TSoftObjectPtr<UItemData> ItemDataAsset);

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Item")
	static TSoftObjectPtr<UStaticMesh> GetItemStaticMesh(TSoftObjectPtr<UItemData> ItemDataAsset);

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Item")
	static bool GetItemIsUsable(TSoftObjectPtr<UItemData> ItemDataAsset);

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Item")
	static bool GetItemIsStackble(TSoftObjectPtr<UItemData> ItemDataAsset);

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Item")
	static int32 GetItemMaxStackSize(TSoftObjectPtr<UItemData> ItemDataAsset);

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Item")
	static bool GetItemIsAllowQuickAccess(TSoftObjectPtr<UItemData> ItemDataAsset);

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Item")
	static TSoftObjectPtr<UTexture2D> GetItemQuickAccessTexture(TSoftObjectPtr<UItemData> ItemDataAsset);

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Item")
	static TSubclassOf<UConsumableBase> GetItemConsumableClass(TSoftObjectPtr<UItemData> ItemDataAsset);

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Item")
	static FName GetItemID(TSoftObjectPtr<UItemData> ItemDataAsset);
	
};
