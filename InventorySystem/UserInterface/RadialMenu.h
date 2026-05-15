// Copyright SPYTHOONA INTERACTIVE. All rights reserved. ABYSSWHISPER is a trademark of SPYTHOONA INTERACTIVE.
// Unreal Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere.All other trademarks are the property of their respective owners.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RadialMenu.generated.h"

UCLASS()
class ABYSSWHISPER_API URadialMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintImplementableEvent)
	void OpenMenu();

	UFUNCTION(BlueprintImplementableEvent)
	void CloseMenu();

	UFUNCTION()
	void UpdateMenu(float AxisX, float AxisY);

protected:

	UFUNCTION(BlueprintImplementableEvent)
	void OnMenuUpdated(int32 CurrentSlot, float SectorAngle);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "RadialMenu")
	int32 SlotsCount = 8;

private:

	FVector2D SmoothedDir = FVector2D::ZeroVector;

};
