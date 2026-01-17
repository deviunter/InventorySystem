// © 2025 Skydream Interactive. All rights reserved. ABYSSWHISPER™ is a trademark of Skydream Interactive.
// Unreal® Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere. All other trademarks are the property of their respective owners.

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

	// ITEM DEFAULTS

	UPROPERTY(EditDefaultsOnly)
	FItemSignature ItemSignature;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FItemSignature GetItemSignature();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FIntPoint GetItemDimension();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ammound")
	int32 GetCurrentAmmound();

	UFUNCTION(BlueprintCallable, Category = "Ammound")
	void SetCurrentAmmound(int32 NewAmmound);

	UFUNCTION(BlueprintCallable)
	void StartUsingItem();

private:

	UPROPERTY()
	int32 Ammound;

};
