// Copyright SPYTHOONA INTERACTIVE. All rights reserved. ABYSSWHISPER is a trademark of SPYTHOONA INTERACTIVE.
// Unreal Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere.All other trademarks are the property of their respective owners.

#include "Systems/InventorySystem/Classes/Items/Health/HealthItemBase.h"

UHealthItemBase::UHealthItemBase()
{
	// TYPE PRESET
	ItemSignature.bAllowQuickAccess = true;
	ItemSignature.bIsStackble = true;
	ItemSignature.bIsUsable = true;
	ItemSignature.ItemType = EItemType::Health;

	// CURRENT CLASS PRESET
	ItemSignature.ItemName = FText::FromString(TEXT("Health Item Base"));
	ItemSignature.ItemID = FName("AIS_HealthItemBase");
}
