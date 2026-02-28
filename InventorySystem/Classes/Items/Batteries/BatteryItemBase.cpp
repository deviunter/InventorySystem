// Copyright SPYTHOONA INTERACTIVE. All rights reserved. ABYSSWHISPER is a trademark of SPYTHOONA INTERACTIVE.
// Unreal Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere.All other trademarks are the property of their respective owners.

// Reflection Engine © 2026 SPYTHOONA INTERACTIVE.All Rights Reserved.
// This software and its source code are the intellectual property of SPYTHOONA INTERACTIVE.
// Unauthorized copying, modification, distribution, or use is strictly prohibited.

#include "Systems/InventorySystem/Classes/Items/Batteries/BatteryItemBase.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerCharacter/ExtendedPlayerCharacter.h"

UBatteryItemBase::UBatteryItemBase()
{
	// TYPE PRESET
	ItemSignature.bIsStackble = true;
	ItemSignature.bIsUsable = true;
	ItemSignature.MaxStackSize = 5;
	ItemSignature.ItemType = EItemType::Battery;
	ItemSignature.ItemDimension = FIntPoint(1, 1);
	bIsItemReusable = false;

	// CURRENT CLASS PRESET
	ItemSignature.ItemName = FText::FromString(TEXT("Battery Item Base"));
	ItemSignature.ItemID = FName("AIS_BatteryItemBase");
}

void UBatteryItemBase::OnItemUsed_Implementation()
{
	Super::OnItemUsed_Implementation();
	Cast<AExtendedPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->RechargeFlashlight(BatteryConsumptionMultiplier);
}
