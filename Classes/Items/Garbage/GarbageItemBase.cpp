// Copyright SPYTHOONA INTERACTIVE. All rights reserved. ABYSSWHISPER is a trademark of SPYTHOONA INTERACTIVE.
// Unreal Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere.All other trademarks are the property of their respective owners.

// Reflection Engine Copyrignt 2026 SPYTHOONA INTERACTIVE.All Rights Reserved.
// This software and its source code are the intellectual property of SPYTHOONA INTERACTIVE.
// Unauthorized copying, modification, distribution, or use is strictly prohibited.

#include "Systems/InventorySystem/Classes/Items/Garbage/GarbageItemBase.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerCharacter/ExtendedPlayerCharacter.h"

UGarbageItemBase::UGarbageItemBase()
{
	// TYPE PRESET
	ItemSignature.ItemType = EItemType::Garbage;
	ItemSignature.bIsStackble = false;
	ItemSignature.bAllowQuickAccess = false;
	ItemSignature.bIsUsable = true;
	ItemSignature.MaxStackSize = INDEX_NONE;

	// CURRENT CLASS PRESET
	ItemSignature.ItemName = FText::FromString(TEXT("Garbage Item Base"));
	ItemSignature.ItemID = FName("AIS_GarbageItemBase");
}

void UGarbageItemBase::OnItemUsed_Implementation()
{
	if (AddedResources.IsEmpty()) return;
	for (FResourceCost LocalResource : AddedResources)
	{
		Cast<AExtendedPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->InventoryComponent->AddResouceAtType(LocalResource.ResourceType, LocalResource.ResourceCost);
	}
}
