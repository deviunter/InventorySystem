// © 2025 Skydream Interactive. All rights reserved. ABYSSWHISPER™ is a trademark of Skydream Interactive.
// Unreal® Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere. All other trademarks are the property of their respective owners.

#include "Systems/InventorySystem/Classes/ItemBase.h"

FItemSignature UItemBase::GetItemSignature()
{
    return ItemSignature;
}

FIntPoint UItemBase::GetItemDimension()
{
    return ItemSignature.ItemDimension;
}

int32 UItemBase::GetCurrentAmmound()
{
    return Ammound;
}

void UItemBase::SetCurrentAmmound(int32 NewAmmound)
{
    Ammound = NewAmmound;
}

void UItemBase::StartUsingItem()
{
}
