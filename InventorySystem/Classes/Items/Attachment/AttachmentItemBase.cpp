// Copyright SPYTHOONA INTERACTIVE. All rights reserved. ABYSSWHISPER is a trademark of SPYTHOONA INTERACTIVE.
// Unreal Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere.All other trademarks are the property of their respective owners.

// Reflection Engine Copyrignt 2026 SPYTHOONA INTERACTIVE.All Rights Reserved.
// This software and its source code are the intellectual property of SPYTHOONA INTERACTIVE.
// Unauthorized copying, modification, distribution, or use is strictly prohibited.

#include "Systems/InventorySystem/Classes/Items/Attachment/AttachmentItemBase.h"
#include "Player/PlayerCharacter/ExtendedPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

UAttachmentItemBase::UAttachmentItemBase()
{
	// TYPE PRESET
	ItemSignature.bIsStackble = false;
	ItemSignature.bIsUsable = true;
	ItemSignature.MaxStackSize = INDEX_NONE;
	ItemSignature.ItemType = EItemType::Attachment;
	bIsItemReusable = false;

	// CURRENT CLASS PRESET
	ItemSignature.ItemName = FText::FromString(TEXT("Attachment Item Base"));
	ItemSignature.ItemID = FName("AIS_AttachmentItemBase");
}

void UAttachmentItemBase::AddImmersiveItem_Implementation()
{
	TObjectPtr<AExtendedPlayerCharacter> Player = Cast<AExtendedPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Player->InventoryComponent->OnItemAdded.AddDynamic(this, &UAttachmentItemBase::OnPlayerInventoryItemAdded);
	Player->InventoryComponent->OnItemRemoved.AddDynamic(this, &UAttachmentItemBase::OnPlayerInventoryItemRemoved);
	OnPlayerInventoryItemAdded(NAME_None);
}

void UAttachmentItemBase::RemoveImmersiveItem_Implementation()
{
	TObjectPtr<AExtendedPlayerCharacter> Player = Cast<AExtendedPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Player->InventoryComponent->OnItemAdded.RemoveDynamic(this, &UAttachmentItemBase::OnPlayerInventoryItemAdded);
	Player->InventoryComponent->OnItemRemoved.RemoveDynamic(this, &UAttachmentItemBase::OnPlayerInventoryItemRemoved);
}

void UAttachmentItemBase::OnItemUsed_Implementation()
{
	TObjectPtr<AExtendedPlayerCharacter> Player = Cast<AExtendedPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!IsValid(Player->GetWeaponAtClass(WeaponAttachmentFor))) return;
	Player->GetWeaponAtClass(WeaponAttachmentFor)->AddWeaponAttachment(WeaponAttachment, AttachmentType, !IsValid(WeaponAttachment));
}

void UAttachmentItemBase::OnPlayerInventoryItemAdded(FName ItemID)
{
	TObjectPtr<AExtendedPlayerCharacter> Player = Cast<AExtendedPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (IsValid(Player->GetWeaponAtClass(WeaponAttachmentFor)))
	{
		ItemSignature.bIsUsable = true;
	}
	else
	{
		ItemSignature.bIsUsable = false;
	}
}

void UAttachmentItemBase::OnPlayerInventoryItemRemoved(FName ItemID, bool bIsItemDestructed)
{
	TObjectPtr<AExtendedPlayerCharacter> Player = Cast<AExtendedPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (IsValid(Player->GetWeaponAtClass(WeaponAttachmentFor)))
	{
		ItemSignature.bIsUsable = true;
	}
	else
	{
		ItemSignature.bIsUsable = false;
	}
}