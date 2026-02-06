// © 2025 Skydream Interactive. All rights reserved. ABYSSWHISPER™ is a trademark of Skydream Interactive.
// Unreal® Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere. All other trademarks are the property of their respective owners.

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
