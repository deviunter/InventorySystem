// © 2025 Skydream Interactive. All rights reserved. ABYSSWHISPER™ is a trademark of Skydream Interactive.
// Unreal® Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere. All other trademarks are the property of their respective owners.

#pragma once

#include "CoreMinimal.h"
#include "Systems/InventorySystem/DataAssets/ItemData.h"
#include "SlotSignature.generated.h"

USTRUCT(BlueprintType)
struct FSlotSignature
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UItemData> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemAmmound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SlotID;
};
