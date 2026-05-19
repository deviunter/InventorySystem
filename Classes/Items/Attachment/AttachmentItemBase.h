// Copyright SPYTHOONA INTERACTIVE. All rights reserved. ABYSSWHISPER is a trademark of SPYTHOONA INTERACTIVE.
// Unreal Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere.All other trademarks are the property of their respective owners.

// Reflection Engine Copyrignt 2026 SPYTHOONA INTERACTIVE.All Rights Reserved.
// This software and its source code are the intellectual property of SPYTHOONA INTERACTIVE.
// Unauthorized copying, modification, distribution, or use is strictly prohibited.

// This class uses experimental dynamic "bIsUsable" parameter.
// An item becomes Usable when Player contain valid reference for weapon at selected class or unusable otherwise

#pragma once

#include "CoreMinimal.h"
#include "Systems/InventorySystem/Classes/ItemBase.h"
#include "Systems/WeaponSystem/FirearmWeapon/WeaponBase.h"
#include "Systems/WeaponSystem/WeaponsComponents/WeaponAttachmentBase.h"
#include "Systems/WeaponSystem/Enumerators/WeaponEnumerators.h"
#include "AttachmentItemBase.generated.h"

UCLASS()
class ABYSSWHISPER_API UAttachmentItemBase : public UItemBase
{
	GENERATED_BODY()

public:

	UAttachmentItemBase();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Attachment")
	TSubclassOf<AWeaponBase> WeaponAttachmentFor;

	UPROPERTY(EditDefaultsOnly, Category = "Attachment")
	TSubclassOf<AWeaponAttachmentBase> WeaponAttachment;

	UPROPERTY(EditDefaultsOnly, Category = "Attachment")
	EWeaponAttachmentType AttachmentType;

	virtual void AddImmersiveItem_Implementation() override;

	virtual void RemoveImmersiveItem_Implementation() override;

	virtual void OnItemUsed_Implementation() override;

private:

	UFUNCTION()
	void OnPlayerInventoryItemAdded(FName ItemID);

	UFUNCTION()
	void OnPlayerInventoryItemRemoved(FName ItemID, bool bIsItemDestructed);

};
