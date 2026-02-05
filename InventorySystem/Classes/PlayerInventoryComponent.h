// © 2025 Skydream Interactive. All rights reserved. ABYSSWHISPER™ is a trademark of Skydream Interactive.
// Unreal® Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere. All other trademarks are the property of their respective owners.

// Reflection Engine © 2025 Deviunter & Skydream Interactive. All Rights Reserved. 
// This software and its source code are the intellectual property of Skydream Interactive.
// Unauthorized copying, modification, distribution, or use is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "Systems/InventorySystem/Classes/InventoryComponent.h"
#include "Systems/InventorySystem/Structures/ResourceSignature.h"
#include "Systems/InventorySystem/Enumerators/InventoryEnumetators.h"
#include "Systems/InventorySystem/Structures/PlayerInventorySaveSignature.h"
#include "Systems/InventorySystem/Structures/KeyDataSignature.h"
#include "PlayerInventoryComponent.generated.h"

UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class ABYSSWHISPER_API UPlayerInventoryComponent : public UInventoryComponent
{
	GENERATED_BODY()

public:

	UPlayerInventoryComponent();

	/*UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SaveGame")
	FPlayerInventorySaveSignature SavePlayerInventory();*/

	// RESOURCES INVENTORY

	UFUNCTION(BlueprintCallable, Category = "Resources")
	EResourceAddType AddResouceAtType(EResourceType ResourceType, int32 AddAmmound);

	UFUNCTION(BlueprintCallable, Category = "Resources")
	FResourceSignature GetResourceAtType(EResourceType ResourceType);

	UFUNCTION(BlueprintCallable, Category = "Resources")
	bool RemoveResourceAtType(EResourceType ResourceType, int32 RemoveAmmound);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Resources")
	TArray<FResourceSignature> GetAllResources() const;

	// KEY DATA ITEMS INVENTORY

	UFUNCTION(BlueprintCallable, Category = "Key Data")
	bool AddKeyDataAtID(FName KeyDataID);

	UFUNCTION(BlueprintCallable, Category = "Key Data")
	bool AddKeyDataAtStructure(FKeyDataSignature KeyDataSignature);

	UFUNCTION(BlueprintCallable, Category = "Key Data")
	bool SetKeyDataIsUsed(FName KeyDataID, bool NewIsUsed);

	UFUNCTION(BlueprintCallable, Category = "Key Data")
	bool RemoveKeyDataAtID(FName KeyDataID);

	UFUNCTION(BlueprintCallable, Category = "Key Data")
	FKeyDataSignature GetKeyDataAtID(FName KeyDataID);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Key Data")
	TArray<FKeyDataSignature> GetKeyDataCollected() const;

	UFUNCTION(BlueprintCallable, Category = "Key Data")
	bool IsKeyDataContains(FName KeyDataID);

	// CHARMS INVENTORY

	UFUNCTION(BlueprintCallable, Category = "Charms")
	bool AddCharmItem(UItemBase* ItemToAdd);

	UFUNCTION(BlueprintCallable, Category = "Charms")
	bool AddCharmItemToSlot(UItemBase* ItemToAdd, int32 SlotIndex);

	UFUNCTION(BlueprintCallable, Category = "Charms")
	bool RemoveCharmItemAtIndex(int32 SlotIndex, bool DestroyItem);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Charms")
	TArray<UItemBase*> GetCharmItems() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Charms")
	UItemBase* GetCharmItemAtIndex(int32 ItemIndex) const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Charms")
	bool IsCharmSlotEmpty(int32 SlotIndex) const;

	UFUNCTION(BlueprintCallable, Category = "Charms")
	void RefreshCharmInventory();

	// QUICK ACCESS SLOTS

	// RESOURCE INVENTORY PARAMETERS

	UPROPERTY(EditDefaultsOnly, Category = "Resources")
	int32 WoodResourceMaxAmount;

	UPROPERTY(EditDefaultsOnly, Category = "Resources")
	int32 MetalResourceMaxAmount;

	UPROPERTY(EditDefaultsOnly, Category = "Resources")
	int32 ElectricalResourceMaxAmount;

	UPROPERTY(EditDefaultsOnly, Category = "Resources")
	int32 ChemicalResourceMaxAmount;

	UPROPERTY(EditDefaultsOnly, Category = "Resources")
	int32 BioResourceMaxAmount;

	// CHARM INVENTORY PARAMETERS

	UPROPERTY(EditDefaultsOnly, Category = "Charms")
	int32 CharmInventoryLength;

private:

	UPROPERTY()
	TArray<FResourceSignature> ResourceList;

	UPROPERTY()
	TArray<FKeyDataSignature> KeyDataList;

	UPROPERTY()
	TArray<UItemBase*> CharmsList;
};
