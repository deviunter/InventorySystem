// Copyright SPYTHOONA INTERACTIVE.All rights reserved.ABYSSWHISPER is a trademark of SPYTHOONA INTERACTIVE.
// Unreal Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere.All other trademarks are the property of their respective owners.

// Reflection Engine © 2026 SPYTHOONA INTERACTIVE.All Rights Reserved.
// This software and its source code are the intellectual property of SPYTHOONA INTERACTIVE.
// Unauthorized copying, modification, distribution, or use is strictly prohibited.

#pragma once

#include "CoreMinimal.h"
#include "Systems/InventorySystem/Classes/ItemBase.h"
#include "BatteryItemBase.generated.h"

UCLASS()
class ABYSSWHISPER_API UBatteryItemBase : public UItemBase
{
	GENERATED_BODY()

public:

	UBatteryItemBase();

	virtual void OnItemUsed_Implementation() override;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Battery")
	float BatteryConsumptionMultiplier;
	
};
