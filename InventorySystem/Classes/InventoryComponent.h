// © 2025 Skydream Interactive. All rights reserved. ABYSSWHISPER™ is a trademark of Skydream Interactive.
// Unreal® Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere. All other trademarks are the property of their respective owners.

// Reflection Engine © 2025 Deviunter & Skydream Interactive. All Rights Reserved. 
// This software and its source code are the intellectual property of Skydream Interactive.
// Unauthorized copying, modification, distribution, or use is strictly prohibited.

// Core inventory system component for managing grid - based inventories.
// Supports items of varying sizes, stacking, adding, removing, splitting, and using items.
// Can be extended for specialized inventories - for player, storage & special loot boxes
// Uses a grid system with rows and columns for spatial item placement.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Systems/InventorySystem/Enumerators/InventoryEnumetators.h"
#include "Systems/InventorySystem/Classes/ItemBase.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ABYSSWHISPER_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UInventoryComponent();

protected:
	
	virtual void BeginPlay() override;

	// Internal notification when an item is added. Can be overridden in child classes.
	UFUNCTION()
	void AddItemNotification(UItemBase* AddedItem, EInventoryAddingType ItemState);

public:	
	
	// BLUEPRINT VISIBLE FUNCTIONS


	// Attempts to add an item to the inventory. Automatically handles stacking and placement.
	UFUNCTION(BlueprintCallable, Category = "Manage")
	EInventoryAddingType AddItem(UItemBase* ItemToAdd);

	// Removes a specified amount of an item from the inventory.
	// If amount becomes zero, the item is removed from slots.
	UFUNCTION(BlueprintCallable, Category = "Manage")
	bool RemoveItem(UItemBase* ItemToAdd, int32 AmmoundToRemove);

	// Drops an item from the inventory (e.g., spawns in world).
	UFUNCTION(BlueprintCallable, Category = "Manage")
	bool DropItem(UItemBase* ItemToDrop, int32 Ammound, bool DestroyAfterDrop);

	// Splits a stack of items into two separate stacks.
	UFUNCTION(BlueprintCallable, Category = "Manage")
	bool SplitItem(int32 TopLeftIndex, int32 NewItemAmmound);

	// Uses an item (triggers its functionality).
	UFUNCTION(BlueprintCallable, Category = "Manage")
	bool UseItem(UItemBase* ItemToUse);

	// Checks if there is room for an item at a specific grid position.
	UFUNCTION(BlueprintCallable, Category = "Manage")
	bool IsRoomAvailable(UItemBase* ItemToAdd, int32 TopLeftIndex);

	// Forces an item into a specific slot (no stacking checks).
	UFUNCTION(BlueprintCallable, Category = "Manage")
	bool AddItemToSlot(UItemBase* ItemToAdd, int32 TopLeftIndex);

	// Converts a linear index to grid coordinates (tile).
	UFUNCTION(BlueprintPure, Category = "Calculation")
	const FItemTile IndexToTile(int32 Index);

	// Converts grid coordinates to a linear index.
	UFUNCTION(BlueprintPure, Category = "Calculation")
	const int32 TileToIndex(FItemTile Tile);

	// Validates if tile coordinates are within inventory bounds.
	UFUNCTION(BlueprintCallable, Category = "Calculation")
	bool IsTileValid(FItemTile Tile);

	// Retrieves item at a specific linear index.
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Item Info")
	UItemBase* GetItemAtIndex(int32 ItemIndex);

	// Gets all inventory slots (including empty ones).
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Item Info")
	TArray<UItemBase*> GetAllItemSlots();

	// Gets a map of all items and their grid positions.
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Item Info")
	TMap<UItemBase*, FItemTile> GetAllItemsAndPosition();

	// Finds first item of a specific class.
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Item Info")
	UItemBase* GetItemAtClass(UItemBase* SearchingClass);

	// Gets total quantity of all items of a specific class.
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Item Info")
	int32 GetItemAmmound(UItemBase* SearchingClass);

	// Array of all inventory slots. Index corresponds to linear grid index.
	UPROPERTY(BlueprintReadOnly)
	TArray<UItemBase*> ItemSlots;

	// Resizes the inventory grid and recreates slot array.
	UFUNCTION(BlueprintCallable, Category = "Size")
	void SetNewInventorySize(int32 Column, int32 Row);

	// Gets the type of inventory (for specialized behavior).
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Inventory Info")
	EInventoryType GetInventoryType();

	// Gets the display name of the inventory.
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Inventory Info")
	FText GetInventoryName();

	// Gets the UI tile size (in pixels).
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Inventory Info")
	float GetItemTile();

	// Number of columns in the inventory grid.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Size")
	int32 ColumnSize;

	// Number of rows in the inventory grid.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Size")
	int32 RowSize;

	// Size of each inventory tile in UI (pixels).
	UPROPERTY(EditDefaultsOnly, Category = "Design")
	float TileSize;

	// Display name for the inventory.
	UPROPERTY(EditDefaultsOnly, Category = "Design")
	FText InventoryName;

private:

	// ADD ITEM VARIANTS

	// Adds item to an existing stack.
	UFUNCTION()
	bool AddItemToStack(UItemBase* ItemToAdd, int32 TopLeftIndex);

	// Places a new item in empty slots.
	UFUNCTION()
	bool AddNewItem(UItemBase* ItemToAdd, int32 TopLeftIndex);

	// Adds item to stack with remainder (if stack would overflow).
	UFUNCTION()
	int32 AddItemToStackWithReminder(UItemBase* ItemToAdd, int32 TopLeftIndex);

	// Checks if an item can be stacked at a position.
	UFUNCTION()
	EStackCheck CheckItemStack(UItemBase* ItemToAdd, int32 TopLeftIndex);

	// Calculates remainder when adding to a stack.
	UFUNCTION()
	int32 CheckReminder(int32 Ammound, UItemBase* CheckedSlot);

	// Updates slot array size based on current grid dimensions.
	UFUNCTION()
	void UpdateInventorySize();

	// Type of inventory (affects behavior and UI).
	UPROPERTY()
	EInventoryType InventoryType;
};
