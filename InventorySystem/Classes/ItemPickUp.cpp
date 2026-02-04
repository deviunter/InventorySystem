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
	SetupPickUpActor();
}

void AItemPickUp::CreateItemObject()
{
	if (IsValid(ItemClass))
	{
		ItemObject = NewObject<UItemBase>(this, ItemClass.Get());
	}
}

void AItemPickUp::SetupPickUpActor()
{
	if (!IsValid(ItemObject) || AsyncLoadingHandle.IsValid()) return;
	if (!ItemObject->GetItemSignature().ItemMesh.IsValid()) return;
	SetActorHiddenInGame(true);
	UpdateInteractionParameters();
	MeshToLoad = ItemObject->GetItemSignature().ItemMesh;
	if (!MeshToLoad.IsPending())
	{
		OnMeshLoaded(MeshToLoad.Get());
		return;
	}
	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
	AsyncLoadingHandle = StreamableManager.RequestAsyncLoad(MeshToLoad.ToSoftObjectPath(), FStreamableDelegate::CreateLambda([this]() {OnMeshLoaded(MeshToLoad.Get());}));
}

void AItemPickUp::OnMeshLoaded(UStaticMesh* StaticMesh)
{
	if (StaticMesh == nullptr) return;
	ItemMesh->SetStaticMesh(StaticMesh);
	InteractCollision->SetBoxExtent(ItemMesh->Bounds.BoxExtent);
	SetActorHiddenInGame(false);
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
