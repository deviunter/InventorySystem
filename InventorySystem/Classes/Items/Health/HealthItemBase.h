// Copyright SPYTHOONA INTERACTIVE. All rights reserved. ABYSSWHISPER is a trademark of SPYTHOONA INTERACTIVE.
// Unreal Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere.All other trademarks are the property of their respective owners.

#pragma once

#include "CoreMinimal.h"
#include "Systems/InventorySystem/Classes/ItemBase.h"
#include "HealthItemBase.generated.h"

UCLASS()
class ABYSSWHISPER_API UHealthItemBase : public UItemBase
{
	GENERATED_BODY()
	
public:

	UHealthItemBase();

	virtual void OnItemUsed_Implementation() override;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	float PercentToAdd;
};
