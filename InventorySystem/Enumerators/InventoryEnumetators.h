// © 2025 Skydream Interactive. All rights reserved. ABYSSWHISPER™ is a trademark of Skydream Interactive.
// Unreal® Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere. All other trademarks are the property of their respective owners.

// Reflection Engine © 2025 Deviunter & Skydream Interactive. All Rights Reserved. 
// This software and its source code are the intellectual property of Skydream Interactive.
// Unauthorized copying, modification, distribution, or use is strictly prohibited.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Weapon UMETA(DisplayName = "Weapon"),
	Ammunition UMETA(DisplayName = "Ammunition"),
	Health UMETA(DisplayName = "Health"),
	Throwable UMETA(DisplayName = "Throwable Weapon"),
	Charms UMETA(DisplayName = "Charms"),
	QuestItem UMETA(DisplayName = "Item for Quest"),
	Garbage UMETA(DisplayName = "Garbage"),
	Miscellaneous UMETA(DisplayName = "Miscellaneous"),
	Development UMETA(DisplayName = "Development")
};

UENUM(BlueprintType)
enum class EInventoryAddingType : uint8
{
	NotAdded UMETA(DisplayName = "Not Added"),
	AddedToNew UMETA(DisplayName = "Added To New Slot"),
	AddedToStack UMETA(DisplayName = "Added To Stack"),
	AddedWithReminderSuccess UMETA(DisplayName = "Added & Reminder Added"),
	AddedWithReminderFailed UMETA(DisplayName = "Added But Reminder Not Added")
};

UENUM(BlueprintType)
enum class EStackCheck : uint8
{
	StackTrue,
	StackFalse,
	StackWithReminder,
	ErrorChecking
};

UENUM(BlueprintType)
enum class EInventoryType : uint8
{
	DefaultInventory,
	PlayerInventory,
	StorageInventory,
	LootboxInventory
};

UENUM(BlueprintType)
enum class EResourceType : uint8
{
	WoodResource,
	MetalResource,
	ElectricalResource,
	ChemicalResource,
	BioResource
};

UENUM(BlueprintType)
enum class EResourceAddType : uint8
{
	Success,
	Fail,
	Partition,
	Error
};