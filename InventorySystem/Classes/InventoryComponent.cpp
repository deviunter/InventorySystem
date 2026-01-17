// © 2025 Skydream Interactive. All rights reserved. ABYSSWHISPERô is a trademark of Skydream Interactive.
// UnrealÆ Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere. All other trademarks are the property of their respective owners.

#include "Systems/InventorySystem/Classes/InventoryComponent.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	RowSize = 4;
	ColumnSize = 5;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	UpdateInventorySize();
}

EInventoryAddingType UInventoryComponent::AddItem(UItemBase* ItemToAdd)
{
	if (ItemToAdd->GetItemDimension().X <= 0 || ItemToAdd->GetItemDimension().Y <= 0)
	{
		return EInventoryAddingType::NotAdded;
	}
	if (ItemToAdd->GetItemDimension().X > ColumnSize || ItemToAdd->GetItemDimension().Y > RowSize)
	{
		return EInventoryAddingType::NotAdded;
	}
	if (IsValid(ItemToAdd))
	{
		for (int32 i = 0; i < ItemSlots.Num(); i++)
		{
			if (IsTileValid(IndexToTile(i)))
			{
				switch (CheckItemStack(ItemToAdd, i))
				{
				case EStackCheck::StackTrue:
					AddItemToStack(ItemToAdd, i);
					return EInventoryAddingType::AddedToStack;
				case EStackCheck::StackFalse:
					if (IsRoomAvailable(ItemToAdd, i))
					{
						AddNewItem(ItemToAdd, i);
					}
					else
					{
						break;
					}
					return EInventoryAddingType::AddedToNew;
				case EStackCheck::StackWithReminder:
					AddItemToStackWithReminder(ItemToAdd, i);
					return EInventoryAddingType::AddedWithReminderSuccess;
				case EStackCheck::ErrorChecking:
					break;
				}
			}
		}
	}
	else
	{
		return EInventoryAddingType::NotAdded;
	}
	return EInventoryAddingType::NotAdded;
}

bool UInventoryComponent::AddItemToStack(UItemBase* ItemToAdd, int32 TopLeftIndex)
{
	int32 TiledIndex;
	for (int32 x = IndexToTile(TopLeftIndex).X; x < ItemToAdd->ItemSignature.ItemDimension.X + IndexToTile(TopLeftIndex).X; x++)
	{
		for (int32 y = IndexToTile(TopLeftIndex).Y; y < ItemToAdd->ItemSignature.ItemDimension.Y + IndexToTile(TopLeftIndex).Y; y++)
		{
			TiledIndex = TileToIndex(FItemTile(x, y));
			if (IsValid(ItemSlots[TiledIndex]) && ItemToAdd->ItemSignature.ItemID == ItemSlots[TiledIndex]->ItemSignature.ItemID)
			{
				ItemSlots[TiledIndex]->SetCurrentAmmound(ItemToAdd->GetCurrentAmmound() + ItemSlots[TiledIndex]->GetCurrentAmmound());
				ItemToAdd->MarkAsGarbage();
				AddItemNotification(ItemSlots[TiledIndex], EInventoryAddingType::AddedToStack);
				return true;
			}
		}
	}
	return false;
}

bool UInventoryComponent::AddNewItem(UItemBase* ItemToAdd, int32 TopLeftIndex)
{
	FItemTile Tile;
	for (int32 x = IndexToTile(TopLeftIndex).X; x < ItemToAdd->GetItemDimension().X + IndexToTile(TopLeftIndex).X; x++)
	{
		for (int32 y = IndexToTile(TopLeftIndex).Y; y < ItemToAdd->GetItemDimension().Y + IndexToTile(TopLeftIndex).Y; y++)
		{
			if (x + ItemToAdd->GetItemDimension().X <= ColumnSize && y + ItemToAdd->GetItemDimension().Y <= RowSize)
			{
				Tile = FItemTile(x, y);
				ItemSlots[TileToIndex(Tile)] = ItemToAdd;
			}
			else
			{
				break;
			}
		}
	}
	AddItemNotification(ItemToAdd, EInventoryAddingType::AddedToNew);
	return true;
}

int32 UInventoryComponent::AddItemToStackWithReminder(UItemBase* ItemToAdd, int32 TopLeftIndex)
{
	int32 MaxSize = ItemToAdd->ItemSignature.MaxStackSize;
	int32 Ammound = ItemToAdd->GetCurrentAmmound();
	int32 TiledIndex;
	int32 Reminder = INDEX_NONE;
	for (int32 x = IndexToTile(TopLeftIndex).X; x < ItemToAdd->ItemSignature.ItemDimension.X + IndexToTile(TopLeftIndex).X; x++)
	{
		for (int32 y = IndexToTile(TopLeftIndex).Y; y < ItemToAdd->ItemSignature.ItemDimension.Y + IndexToTile(TopLeftIndex).Y; y++)
		{
			TiledIndex = TileToIndex(FItemTile(x, y));
			int32 CurrentAmmound = ItemSlots[TiledIndex]->GetCurrentAmmound();
			if (IsValid(ItemToAdd) && ItemToAdd->ItemSignature.ItemID == ItemSlots[TiledIndex]->ItemSignature.ItemID)
			{
				int32 Addenum = MaxSize - CurrentAmmound;
				if (Addenum < Ammound)
				{
					ItemSlots[TiledIndex]->SetCurrentAmmound(ItemSlots[TiledIndex]->GetCurrentAmmound() + Addenum);
					Reminder = Ammound - Addenum;
				}
				else
				{
					ItemSlots[TiledIndex]->SetCurrentAmmound(Ammound);
					Reminder = INDEX_NONE;
				}
			}
		}
	}
	if (Reminder != INDEX_NONE)
	{
		ItemToAdd->SetCurrentAmmound(Reminder);
		AddItem(ItemToAdd);
		AddItemNotification(ItemToAdd, EInventoryAddingType::AddedWithReminderSuccess);
		return INDEX_NONE;
	}
	return INDEX_NONE;
}

// ›“Œ —“¿–€… ¬¿–»¿Õ“ –≈¿À»«¿÷»» ›“Œ… ‘”Õ ÷»», ŒÕ »—œ–¿¬≈Õ, ÕŒ ŒÕ Õ≈ œ–≈ƒ”—Ã¿“–»¬¿≈“ “Œ√Œ, ◊“Œ  ŒÀ-¬Œ ”ƒ¿Àﬂ≈ÃŒ√Œ ÃŒ∆≈“ ¡€“‹ ¡ŒÀ‹ÿ≈ ◊≈Ã  ŒÀ-¬Œ œ–≈ƒÃ≈“¿ ¬ —ÀŒ“≈.
bool UInventoryComponent::RemoveItem(UItemBase* ItemToRemove, int32 AmmoundToRemove)
{
	for (int32 i = 0; i < ItemSlots.Num(); i++)
	{
		if (ItemToRemove == ItemSlots[i])
		{
			if (ItemSlots[i]->GetCurrentAmmound() > AmmoundToRemove)
			{
				int32 NewAmmo = ItemSlots[i]->GetCurrentAmmound() - AmmoundToRemove;
				ItemSlots[i]->SetCurrentAmmound(NewAmmo);
			}
			else if (ItemSlots[i]->GetCurrentAmmound() == AmmoundToRemove)
			{
				ItemSlots[i]->MarkAsGarbage();
				ItemSlots[i] = nullptr;
			}
			else
			{
				// LATER
			}
		}
	}
	return true;
}

bool UInventoryComponent::DropItem(UItemBase* ItemToRemove, int32 Ammound, bool DestroyAfterDrop)
{
	return false;
}

bool UInventoryComponent::SplitItem(int32 TopLeftIndex, int32 NewItemAmmound)
{
	if (!IsValid(ItemSlots[TopLeftIndex]))
	{
		return false;
	}
	if (ItemSlots[TopLeftIndex]->GetItemSignature().bIsStackble && ItemSlots[TopLeftIndex]->GetCurrentAmmound() > 1)
	{
		// DUBLICATE CLASS
		TSubclassOf<UItemBase> LocalClass = ItemSlots[TopLeftIndex]->GetClass();
		int32 NewAmmoundToOldItem = ItemSlots[TopLeftIndex]->GetCurrentAmmound() - NewItemAmmound;
		ItemSlots[TopLeftIndex]->SetCurrentAmmound(NewAmmoundToOldItem);
		UItemBase* LocalNewItem = NewObject<UItemBase>(this, LocalClass.Get());
		// ADD NEW ITEM TO INVENTORY
		for (int32 i = 0; i < ItemSlots.Num(); i++)
		{
			if (IsTileValid(IndexToTile(i)))
			{
				if (IsRoomAvailable(LocalNewItem, i))
				{
					AddNewItem(LocalNewItem, i);
				}
				else
				{
					break;
				}
			}
		}
	}
}

bool UInventoryComponent::UseItem(UItemBase* ItemToUse)
{
	if (IsValid(ItemToUse))
	{
		ItemToUse->StartUsingItem();
	}
}

bool UInventoryComponent::IsRoomAvailable(UItemBase* ItemToAdd, int32 TopLeftIndex)
{
	FItemTile StartTile = IndexToTile(TopLeftIndex);
	if (!IsTileValid(StartTile))
	{
		return false;
	}
	if (StartTile.X + ItemToAdd->GetItemDimension().X > ColumnSize || StartTile.Y + ItemToAdd->GetItemDimension().Y > RowSize)
	{
		return false;
	}
	FItemTile Tile;
	for (int32 x = IndexToTile(TopLeftIndex).X; x < ItemToAdd->GetItemDimension().X + IndexToTile(TopLeftIndex).X; x++)
	{
		for (int32 y = IndexToTile(TopLeftIndex).Y; y < ItemToAdd->GetItemDimension().Y + IndexToTile(TopLeftIndex).Y; y++)
		{
			Tile = FItemTile(x, y);
			if (!IsTileValid(Tile))
			{
				return false;
			}
			if (IsValid(ItemSlots[TileToIndex(Tile)]))
			{
				return false;
			}
			
		}
	}
	return true;
}

void UInventoryComponent::AddItemNotification(UItemBase* AddedItem, EInventoryAddingType ItemState)
{
	// THIS FUNCTION WILL BE DEFINED IN PLAYER INVENTORY COMPONENT CHILD CLASS
}

bool UInventoryComponent::IsTileValid(FItemTile Tile)
{
	if (Tile.X >= 0 && Tile.X < ColumnSize && Tile.Y >= 0 && Tile.Y < RowSize)
	{
		return true;
	}
	else
	{
		return false;
	}
}

EStackCheck UInventoryComponent::CheckItemStack(UItemBase* ItemToAdd, int32 TopLeftIndex)
{
	if (ItemToAdd->GetItemDimension().X <= 0 || ItemToAdd->GetItemDimension().Y <= 0)
	{
		return EStackCheck::ErrorChecking;
	}
	FItemTile StartTile = IndexToTile(TopLeftIndex);
	if (!IsTileValid(StartTile))
	{
		return EStackCheck::ErrorChecking;
	}
	if (StartTile.X + ItemToAdd->GetItemDimension().X > ColumnSize || StartTile.Y + ItemToAdd->GetItemDimension().Y > RowSize)
	{
		return EStackCheck::ErrorChecking;
	}
	if (IsValid(ItemToAdd) && IsTileValid(IndexToTile(TopLeftIndex)))
	{
		for (int32 x = IndexToTile(TopLeftIndex).X; x < ItemToAdd->GetItemDimension().X + IndexToTile(TopLeftIndex).X; x++)
		{
			for (int32 y = IndexToTile(TopLeftIndex).Y; y < ItemToAdd->GetItemDimension().Y + IndexToTile(TopLeftIndex).Y; y++)
			{
				if (IsValid(ItemSlots[TileToIndex(FItemTile(x, y))]))
				{
					if (ItemToAdd->ItemSignature.ItemID == ItemSlots[TileToIndex(FItemTile(x, y))]->ItemSignature.ItemID && ItemSlots[TileToIndex(FItemTile(x, y))]->GetCurrentAmmound() < ItemSlots[TileToIndex(FItemTile(x, y))]->ItemSignature.MaxStackSize)
					{
						if (CheckReminder(ItemToAdd->GetCurrentAmmound(), ItemSlots[TileToIndex(FItemTile(x, y))]) != INDEX_NONE)
						{
							return EStackCheck::StackWithReminder;
						}
						else
						{
							return EStackCheck::StackTrue;
						}
					}
					else
					{
						return EStackCheck::StackFalse;
					}
				}
			}
		}
		return EStackCheck::StackFalse;
	}
	else
	{
		return EStackCheck::ErrorChecking;
	}
}

int32 UInventoryComponent::CheckReminder(int32 Ammound, UItemBase* CheckedSlot)
{
	int32 CurrentAmmound = CheckedSlot->GetCurrentAmmound();
	int32 MaxAmmound = CheckedSlot->ItemSignature.MaxStackSize;
	if (CurrentAmmound + Ammound <= MaxAmmound)
	{
		return INDEX_NONE;
	}
	else
	{
		int32 Max = CurrentAmmound + Ammound;
		return Max - MaxAmmound;
	}
	//return INDEX_NONE;
}

const FItemTile UInventoryComponent::IndexToTile(int32 Index)
{
	return FItemTile(Index % ColumnSize, Index / ColumnSize);
}

const int32 UInventoryComponent::TileToIndex(FItemTile Tile)
{
	int32 X = Tile.X;
	int32 Y = ColumnSize * Tile.Y;
	return X + Y;
}

UItemBase* UInventoryComponent::GetItemAtIndex(int32 ItemIndex)
{
	return ItemSlots[ItemIndex];
}

TArray<UItemBase*> UInventoryComponent::GetAllItemSlots()
{
	return ItemSlots;
}

//const TMap<FSlotSignature, FItemTile>& UInventoryComponent::GetAllItemsAndPosition()
//{
//	TMap<FSlotSignature, FItemTile> LocalItems;
//	LocalItems.Empty();
//	for (int32 i = 0; i < ItemSlots.Num(); i++)
//	{
//		if (!LocalItems.Contains(ItemSlots[i]) && UInventoryStaticsLibrary::IsSlotValid(ItemSlots[i]))
//		{
//			LocalItems.Add(ItemSlots[i], IndexToTile(i));
//		}
//	}
//	return LocalItems;
//}

// I DO THIS LATER (2 FUNC LOWER)

UItemBase* UInventoryComponent::GetItemAtClass(UItemBase* SearchingClass)
{
	return nullptr;
}

int32 UInventoryComponent::GetItemAmmound(UItemBase* SearchingClass)
{
	return int32();
}

void UInventoryComponent::SetNewInventorySize(int32 Column, int32 Row)
{
	ColumnSize = Column;
	RowSize = Row;
	UpdateInventorySize();
}

void UInventoryComponent::UpdateInventorySize()
{
	ItemSlots.SetNum(ColumnSize * RowSize);
}

// I DO THIS LATER ^^
