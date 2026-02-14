// Copyright SPYTHOONA INTERACTIVE. All rights reserved. ABYSSWHISPER is a trademark of SPYTHOONA INTERACTIVE.
// Unreal Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere.All other trademarks are the property of their respective owners.

#include "Systems/InventorySystem/Classes/Items/Ammunition/AmmunitionItemBase.h"

UAmmunitionItemBase::UAmmunitionItemBase()
{
	// TYPE PRESET
	ItemSignature.bIsStackble = true;
	ItemSignature.bIsUsable = false;
	ItemSignature.ItemDimension = FIntPoint(1, 1);
	ItemSignature.ItemType = EItemType::Ammunition;

	// CURRENT CLASS PRESET
	ItemSignature.ItemName = FText::FromString(TEXT("Ammunition Item Base"));
	ItemSignature.ItemID = FName("AIS_AmmunitionItemBase");
}
