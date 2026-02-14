// Copyright SPYTHOONA INTERACTIVE. All rights reserved. ABYSSWHISPER is a trademark of SPYTHOONA INTERACTIVE.
// Unreal Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere.All other trademarks are the property of their respective owners.

// Reflection Engine © 2026 SPYTHOONA INTERACTIVE.All Rights Reserved.
// This software and its source code are the intellectual property of SPYTHOONA INTERACTIVE.
// Unauthorized copying, modification, distribution, or use is strictly prohibited.

#include "Systems/InventorySystem/Classes/Items/Charms/CharmItemBase.h"
#include "Core/Interfaces/ActorsInterface.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

UCharmItemBase::UCharmItemBase()
{
	// TYPE PRESET
	ItemSignature.bAllowQuickAccess = false;
	ItemSignature.bIsStackble = false;
	ItemSignature.bIsUsable = false;
	ItemSignature.ItemDimension = FIntPoint(1, 1);
	ItemSignature.MaxStackSize = INDEX_NONE;
	ItemSignature.ItemType = EItemType::Charms;

	// CURRENT CLASS PRESET
	ItemSignature.ItemName = FText::FromString(TEXT("Charm Item Base"));
	ItemSignature.ItemID = FName("Charm Item Base");
}

void UCharmItemBase::CharmAdded()
{
	TObjectPtr<ACharacter> LocalPlayer = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	IActorsInterface::Execute_AddToActorGameplayTags((UObject*)LocalPlayer, CharmEffects);
}

void UCharmItemBase::CharmRemoved()
{
	TObjectPtr<ACharacter> LocalPlayer = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	IActorsInterface::Execute_RemoveActorGameplayTags((UObject*)LocalPlayer, CharmEffects);
}
