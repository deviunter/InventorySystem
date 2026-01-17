// © 2025 Skydream Interactive. All rights reserved. ABYSSWHISPER™ is a trademark of Skydream Interactive.
// Unreal® Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere. All other trademarks are the property of their respective owners.

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

public:	
	
	// BLUEPRINT VISIBLE FUNCTIONS

	UFUNCTION(BlueprintCallable, Category = "Manage")
	EInventoryAddingType AddItem(UItemBase* ItemToAdd);

	UFUNCTION(BlueprintCallable, Category = "Manage")
	bool RemoveItem(UItemBase* ItemToAdd, int32 AmmoundToRemove);

	UFUNCTION(BlueprintCallable, Category = "Manage")
	bool DropItem(UItemBase* ItemToDrop, int32 Ammound, bool DestroyAfterDrop);

	UFUNCTION(BlueprintCallable, Category = "Manage")
	bool SplitItem(int32 TopLeftIndex, int32 NewItemAmmound);

	UFUNCTION(BlueprintCallable, Category = "Manage")
	bool UseItem(UItemBase* ItemToUse);

	UFUNCTION(BlueprintCallable, Category = "Manage")
	bool IsRoomAvailable(UItemBase* ItemToAdd, int32 TopLeftIndex);

	UFUNCTION()
	void AddItemNotification(UItemBase* AddedItem, EInventoryAddingType ItemState);

	UFUNCTION()
	EStackCheck CheckItemStack(UItemBase* ItemToAdd, int32 TopLeftIndex);

	UFUNCTION()
	int32 CheckReminder(int32 Ammound, UItemBase* CheckedSlot);

	UFUNCTION(BlueprintPure, Category = "Calculation")
	const FItemTile IndexToTile(int32 Index);

	UFUNCTION(BlueprintPure, Category = "Calculation")
	const int32 TileToIndex(FItemTile Tile);

	UFUNCTION(BlueprintCallable, Category = "Calculation")
	bool IsTileValid(FItemTile Tile);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Item Info")
	UItemBase* GetItemAtIndex(int32 ItemIndex);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Item Info")
	TArray<UItemBase*> GetAllItemSlots();

	//UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Item Info")
	//const TMap<FSlotSignature, FItemTile>& GetAllItemsAndPosition();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Item Info")
	UItemBase* GetItemAtClass(UItemBase* SearchingClass);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Item Info")
	int32 GetItemAmmound(UItemBase* SearchingClass);

	UPROPERTY(BlueprintReadOnly)
	TArray<UItemBase*> ItemSlots;

	UFUNCTION(BlueprintCallable, Category = "Size")
	void SetNewInventorySize(int32 Column, int32 Row);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Size")
	int32 ColumnSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Size")
	int32 RowSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Design")
	float TileSize;

private:

	// ADD ITEM VARIANTS

	UFUNCTION()
	bool AddItemToStack(UItemBase* ItemToAdd, int32 TopLeftIndex);

	UFUNCTION()
	bool AddNewItem(UItemBase* ItemToAdd, int32 TopLeftIndex);

	UFUNCTION()
	int32 AddItemToStackWithReminder(UItemBase* ItemToAdd, int32 TopLeftIndex);

	UFUNCTION()
	void UpdateInventorySize();
};
