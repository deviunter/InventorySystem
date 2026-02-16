// Copyright SPYTHOONA INTERACTIVE. All rights reserved. ABYSSWHISPER is a trademark of SPYTHOONA INTERACTIVE.
// Unreal Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere.All other trademarks are the property of their respective owners.

#include "Systems/InventorySystem/Classes/Items/Quest/QuestItemBase.h"

UQuestItemBase::UQuestItemBase()
{
	// TYPE PRESET
	ItemSignature.ItemType = EItemType::QuestItem;
	ItemSignature.bIsUsable = false;
	ItemSignature.bAllowQuickAccess = false;

	// CURRENT CLASS PRESET
	ItemSignature.ItemName = FText::FromString(TEXT("Quest Item Base"));
	ItemSignature.ItemID = FName("AIS_QuestItemBase");
}
