// Copyright SPYTHOONA INTERACTIVE. All rights reserved. ABYSSWHISPER is a trademark of SPYTHOONA INTERACTIVE.
// Unreal Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere.All other trademarks are the property of their respective owners.

#include "Systems/InventorySystem/Classes/Items/Weapon/WeaponItemBase.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerCharacter/ExtendedPlayerCharacter.h"

UWeaponItemBase::UWeaponItemBase()
{
	// TYPE PRESET
	ItemSignature.bAllowQuickAccess = true;
	ItemSignature.bIsStackble = false;
	ItemSignature.bIsUsable = true;
	ItemSignature.MaxStackSize = INDEX_NONE;
	ItemSignature.ItemType = EItemType::Weapon;
	bIsItemUsingImmediately = false;

	// CURRENT CLASS PRESET
	ItemSignature.ItemName = FText::FromString(TEXT("Weapon Item Base"));
	ItemSignature.ItemID = FName("AIS_WeaponItemBase");
}

void UWeaponItemBase::AddImmersiveItem_Implementation()
{
	Super::AddImmersiveItem_Implementation();
	Cast<AExtendedPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->AddWeaponToPlayer(WeaponClass);
}

void UWeaponItemBase::RemoveImmersiveItem_Implementation()
{
	Super::RemoveImmersiveItem_Implementation();
	Cast<AExtendedPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->RemoveWeaponFromPlayer(WeaponClass);
}
