// © 2025 Skydream Interactive. All rights reserved. ABYSSWHISPER™ is a trademark of Skydream Interactive.
// Unreal® Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere. All other trademarks are the property of their respective owners.

// Reflection Engine © 2025 Deviunter & Skydream Interactive. All Rights Reserved. 
// This software and its source code are the intellectual property of Skydream Interactive.
// Unauthorized copying, modification, distribution, or use is strictly prohibited.

#include "Systems/InventorySystem/Classes/ItemBase.h"

UItemBase::UItemBase()
{
    
}

const FItemSignature UItemBase::GetItemSignature()
{
    return ItemSignature;
}

FIntPoint UItemBase::GetItemDimension() const
{
    return ItemSignature.ItemDimension;
}

int32 UItemBase::GetCurrentAmmound() const
{
    return Ammound;
}

void UItemBase::SetCurrentAmmound(int32 NewAmmound)
{
    Ammound = NewAmmound;
}

bool UItemBase::IsItemUsingImmediately() const
{
    return bIsItemUsingImmediately;
}

void UItemBase::StartUsingItem()
{
    if (bIsItemUsingImmediately)
    {
        OnItemUsed();
    }
}

void UItemBase::StopUsingItem()
{
}

void UItemBase::CancelUsingItem()
{
}

void UItemBase::AddImmersiveItem_Implementation()
{
}

void UItemBase::RemoveImmersiveItem_Implementation()
{
}

void UItemBase::OnItemUsed_Implementation()
{
}

void UItemBase::CallItemSkill_Implementation()
{
}
