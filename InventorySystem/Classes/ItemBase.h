// Copyright SPYTHOONA INTERACTIVE. All rights reserved. ABYSSWHISPER is a trademark of SPYTHOONA INTERACTIVE.
// Unreal Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere.All other trademarks are the property of their respective owners.

// Reflection Engine © 2026 SPYTHOONA INTERACTIVE.All Rights Reserved.
// This software and its source code are the intellectual property of SPYTHOONA INTERACTIVE.
// Unauthorized copying, modification, distribution, or use is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Systems/InventorySystem/Structures/ItemSignature.h"
#include "ItemBase.generated.h"

UCLASS(Blueprintable, BlueprintType)
class ABYSSWHISPER_API UItemBase : public UObject
{
	GENERATED_BODY()

public:

	UItemBase();

	// ITEM DEFAULTS

	UFUNCTION(BlueprintCallable, BlueprintPure)
	const FItemSignature GetItemSignature();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FIntPoint GetItemDimension() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ammound")
	int32 GetCurrentAmmound() const;

	UFUNCTION(BlueprintCallable, Category = "Ammound")
	void SetCurrentAmmound(int32 NewAmmound);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Item")
	bool GetIsItemReusable() const;

	// ITEM USING & INTERACTION

	UFUNCTION(BlueprintCallable, Category = "Item Interaction")
	void StartUsingItem();

	UFUNCTION(BlueprintCallable, Category = "Item Interaction")
	void StopUsingItem();

	UFUNCTION(BlueprintCallable, Category = "Item Interaction")
	void CancelUsingItem();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Item Interaction")
	void AddImmersiveItem();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Item Interaction")
	void RemoveImmersiveItem();

	virtual void AddImmersiveItem_Implementation();

	virtual void RemoveImmersiveItem_Implementation();

protected:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Item Interaction")
	void OnItemUsed();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Item Interaction")
	void CallItemSkill();

	virtual void OnItemUsed_Implementation();

	virtual void CallItemSkill_Implementation();

	UPROPERTY(EditDefaultsOnly)
	bool bIsItemReusable;

	UPROPERTY(EditDefaultsOnly)
	FItemSignature ItemSignature;

private:

	UPROPERTY()
	int32 Ammound;

};
