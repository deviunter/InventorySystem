// Copyright SPYTHOONA INTERACTIVE. All rights reserved. ABYSSWHISPER is a trademark of SPYTHOONA INTERACTIVE.
// Unreal Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere.All other trademarks are the property of their respective owners.

// Reflection Engine Copyrignt 2026 SPYTHOONA INTERACTIVE.All Rights Reserved.
// This software and its source code are the intellectual property of SPYTHOONA INTERACTIVE.
// Unauthorized copying, modification, distribution, or use is strictly prohibited.

#include "Systems/InventorySystem/Classes/Items/Throwable/ThrowableItemBase.h"

UThrowableItemBase::UThrowableItemBase()
{
	// TYPE PRESET
	ItemSignature.bAllowQuickAccess = true;
	ItemSignature.bIsStackble = true;
	ItemSignature.bIsUsable = true;
	ItemSignature.ItemType = EItemType::Throwable;
	ItemSignature.MaxStackSize = 5;
	bIsItemReusable = true;

	// CURRENT CLASS PRESET
	ItemSignature.ItemName = FText::FromString(TEXT("Throwable Item Base"));
	ItemSignature.ItemID = FName("AIS_ThrowableItemBase");
}
