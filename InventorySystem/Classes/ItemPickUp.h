// © 2025 Skydream Interactive. All rights reserved. ABYSSWHISPER™ is a trademark of Skydream Interactive.
// Unreal® Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere. All other trademarks are the property of their respective owners.

#pragma once

#include "CoreMinimal.h"
#include "Core/Actors/InteractiveActors/InteractiveActor.h"
#include "Systems/InventorySystem/Classes/ItemBase.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "ItemPickUp.generated.h"

UCLASS()
class ABYSSWHISPER_API AItemPickUp : public AInteractiveActor
{
	GENERATED_BODY()

public:

	AItemPickUp();

	UPROPERTY(EditAnywhere, Category = "Item")
	TSubclassOf<UItemBase> ItemClass;
	
	UPROPERTY(EditAnywhere, Category = "Item")
	UItemBase* ItemObject;

protected:

	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void CreateItemObject();

	UFUNCTION()
	void SetupPickUpActor();

	TSharedPtr<FStreamableHandle> AsyncLoadingHandle;

	UPROPERTY()
	TSoftObjectPtr<UStaticMesh> MeshToLoad;

	UFUNCTION()
	void OnMeshLoaded(UStaticMesh* StaticMesh);

	UFUNCTION()
	void UpdateInteractionParameters();
};
