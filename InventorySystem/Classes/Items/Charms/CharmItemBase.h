// © 2025 Skydream Interactive. All rights reserved. ABYSSWHISPER™ is a trademark of Skydream Interactive.
// Unreal® Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere. All other trademarks are the property of their respective owners.

#pragma once

#include "CoreMinimal.h"
#include "Systems/InventorySystem/Classes/ItemBase.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "CharmItemBase.generated.h"

UCLASS()
class ABYSSWHISPER_API UCharmItemBase : public UItemBase
{
	GENERATED_BODY()

public:

	UCharmItemBase();

	UFUNCTION(BlueprintCallable, Category = "Charms")
	void CharmAdded();

	UFUNCTION(BlueprintCallable, Category = "Charms")
	void CharmRemoved();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Charm")
	TArray<FGameplayTag> CharmEffects;

};
