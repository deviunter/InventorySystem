// © 2025 Skydream Interactive. All rights reserved. ABYSSWHISPER™ is a trademark of Skydream Interactive.
// Unreal® Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere. All other trademarks are the property of their respective owners.

#include "Systems/InventorySystem/Classes/ItemPickUp.h"
#include "Internationalization/StringTable.h"


AItemPickUp::AItemPickUp()
{
	AcceptableInteractionDistance = 200.0f;
}

void AItemPickUp::BeginPlay()
{
	if (!IsValid(ItemObject)) CreateItemObject();
	/*else SetupPickUpActor();*/
}

void AItemPickUp::CreateItemObject()
{
	if (IsValid(ItemClass))
	{
		ItemObject = NewObject<UItemBase>(this, ItemClass.Get());
		if (!IsValid(ItemObject))
		{
			GEngine->AddOnScreenDebugMessage(0, 5, FColor::Red, FString("Item Object Invalid< abort///"));
			return;
		}
		GEngine->AddOnScreenDebugMessage(1, 5, FColor::Cyan, FString("Item Created"));
		SetupPickUpActor();
	}
}

void AItemPickUp::SetupPickUpActor()
{
	SetActorHiddenInGame(true);
	GEngine->AddOnScreenDebugMessage(2, 5, FColor::Cyan, FString("ItemObject Validation"));
	if (!IsValid(ItemObject)) return;
	GEngine->AddOnScreenDebugMessage(3, 5, FColor::Cyan, FString("Async Loading Validation"));
	if (AsyncLoadingHandle.IsValid()) return;
	GEngine->AddOnScreenDebugMessage(4, 5, FColor::Cyan, FString("Item Mesh Validation"));
	if (!ItemObject->GetItemSignature().ItemMesh.IsValid())
	{
		GEngine->AddOnScreenDebugMessage(4, 5, FColor::Red, FString("Mesh invalid abort..."));
		return;
	}
	UpdateInteractionParameters();
	MeshToLoad = ItemObject->GetItemSignature().ItemMesh;
	if (!MeshToLoad.IsPending())
	{
		OnMeshLoaded(MeshToLoad.Get());
		return;
	}
	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
	GEngine->AddOnScreenDebugMessage(5, 5, FColor::Cyan, FString("Start Data Loading"));
	AsyncLoadingHandle = StreamableManager.RequestAsyncLoad(MeshToLoad.ToSoftObjectPath(), FStreamableDelegate::CreateLambda([this]() {OnMeshLoaded(MeshToLoad.Get());}));
}

void AItemPickUp::OnMeshLoaded(UStaticMesh* StaticMesh)
{
	if (StaticMesh == nullptr) return;
	ItemMesh->SetStaticMesh(StaticMesh);
	InteractCollision->SetBoxExtent(ItemMesh->Bounds.BoxExtent);
	SetActorHiddenInGame(false);
	GEngine->AddOnScreenDebugMessage(6, 5, FColor::Cyan, FString("Static Mesh Loaded"));
	AsyncLoadingHandle.Reset();
}

void AItemPickUp::UpdateInteractionParameters()
{
	if (!IsValid(ItemObject)) return;
	FItemSignature ItemSignature = ItemObject->GetItemSignature();
	if (!ItemSignature.bIsUsable) return;
	bHasInteractionMessage = true;
	FirstInteractionMessage = FText::FromStringTable(FName("InteractionMessages"), FTextKey("Interaction_PickUp"));
	SecondInteractionMessage = FText::FromStringTable(FName("InteractionMessages"), FTextKey("Interaction_Use"));
	bHasMultipleInteraction = true;
}
