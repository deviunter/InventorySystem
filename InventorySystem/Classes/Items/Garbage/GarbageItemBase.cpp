// Copyright SPYTHOONA INTERACTIVE. All rights reserved. ABYSSWHISPER is a trademark of SPYTHOONA INTERACTIVE.
// Unreal Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere.All other trademarks are the property of their respective owners.

#include "Systems/InventorySystem/Classes/Items/Garbage/GarbageItemBase.h"

UGarbageItemBase::UGarbageItemBase()
{
	// TYPE PRESET
	ItemSignature.ItemType = EItemType::Garbage;

	// CURRENT CLASS PRESET
	ItemSignature.ItemName = FText::FromString(TEXT("Garbage Item Base"));
	ItemSignature.ItemID = FName("AIS_GarbageItemBase");
}
