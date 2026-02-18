// Copyright SPYTHOONA INTERACTIVE. All rights reserved. ABYSSWHISPER is a trademark of SPYTHOONA INTERACTIVE.
// Unreal Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere.All other trademarks are the property of their respective owners.

// Reflection Engine © 2026 SPYTHOONA INTERACTIVE.All Rights Reserved.
// This software and its source code are the intellectual property of SPYTHOONA INTERACTIVE.
// Unauthorized copying, modification, distribution, or use is strictly prohibited.

#include "Systems/InventorySystem/Classes/InventoryComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Core/Interfaces/WidgetsInterface.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	RowSize = 4;
	ColumnSize = 5;

	TileSize = 90.0f;
	InventoryType = EInventoryType::DefaultInventory;

	GetWidgetClass();
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	CreateGridWidget();
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
	for (int32 x = IndexToTile(TopLeftIndex).X; x < ItemToAdd->GetItemDimension().X + IndexToTile(TopLeftIndex).X; x++)
	{
		for (int32 y = IndexToTile(TopLeftIndex).Y; y < ItemToAdd->GetItemDimension().Y + IndexToTile(TopLeftIndex).Y; y++)
		{
			TiledIndex = TileToIndex(FItemTile(x, y));
			if (IsValid(ItemSlots[TiledIndex]) && ItemToAdd->GetItemSignature().ItemID == ItemSlots[TiledIndex]->GetItemSignature().ItemID)
			{
				ItemSlots[TiledIndex]->SetCurrentAmmound(ItemToAdd->GetCurrentAmmound() + ItemSlots[TiledIndex]->GetCurrentAmmound());
				ItemToAdd->MarkAsGarbage();
				AddItemNotification(ItemSlots[TiledIndex], EInventoryAddingType::AddedToStack);
				if (OnItemAdded.IsBound()) OnItemAdded.Broadcast(ItemToAdd->GetItemSignature().ItemID);
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
	ItemToAdd->AddImmersiveItem();
	if (OnItemAdded.IsBound()) OnItemAdded.Broadcast(ItemToAdd->GetItemSignature().ItemID);
	AddItemNotification(ItemToAdd, EInventoryAddingType::AddedToNew);
	return true;
}

int32 UInventoryComponent::AddItemToStackWithReminder(UItemBase* ItemToAdd, int32 TopLeftIndex)
{
	int32 MaxSize = ItemToAdd->GetItemSignature().MaxStackSize;
	int32 Ammound = ItemToAdd->GetCurrentAmmound();
	int32 TiledIndex;
	int32 Reminder = INDEX_NONE;
	for (int32 x = IndexToTile(TopLeftIndex).X; x < ItemToAdd->GetItemDimension().X + IndexToTile(TopLeftIndex).X; x++)
	{
		for (int32 y = IndexToTile(TopLeftIndex).Y; y < ItemToAdd->GetItemDimension().Y + IndexToTile(TopLeftIndex).Y; y++)
		{
			TiledIndex = TileToIndex(FItemTile(x, y));
			int32 CurrentAmmound = ItemSlots[TiledIndex]->GetCurrentAmmound();
			if (IsValid(ItemToAdd) && ItemToAdd->GetItemSignature().ItemID == ItemSlots[TiledIndex]->GetItemSignature().ItemID)
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
	if (OnItemAdded.IsBound()) OnItemAdded.Broadcast(ItemToAdd->GetItemSignature().ItemID);
	if (Reminder != INDEX_NONE)
	{
		ItemToAdd->SetCurrentAmmound(Reminder);
		AddItem(ItemToAdd);
		AddItemNotification(ItemToAdd, EInventoryAddingType::AddedWithReminderSuccess);
		return INDEX_NONE;
	}
	return INDEX_NONE;
}

bool UInventoryComponent::RemoveItem(UItemBase* ItemToRemove, int32 AmmoundToRemove, bool DestroyItem)
{
	if (!IsValid(ItemToRemove)) return false;
	bool bSuccessFinded = false;
	for (UItemBase* LocalItem : ItemSlots)
	{
		if (LocalItem == ItemToRemove)
		{
			bSuccessFinded = true;
			break;
		}
	}
	if (!bSuccessFinded) return false;
	FName ItemID = ItemToRemove->GetItemSignature().ItemID;
	if (ItemToRemove->GetItemSignature().bIsStackble)
	{
		if (ItemToRemove->GetCurrentAmmound() > AmmoundToRemove)
		{
			int32 NewAmmo = ItemToRemove->GetCurrentAmmound() - AmmoundToRemove;
			ItemToRemove->SetCurrentAmmound(NewAmmo);
			if (OnItemRemoved.IsBound()) OnItemRemoved.Broadcast(ItemID, DestroyItem);
			UpdateGridWidget();
			return true;
		}
		else if (ItemToRemove->GetCurrentAmmound() == AmmoundToRemove)
		{
			ItemToRemove->RemoveImmersiveItem();
			for (int32 i = 0; i < ItemSlots.Num(); i++)
			{
				if (ItemSlots[i] == ItemToRemove)
				{
					ItemSlots[i] = nullptr;
				}
			}
			if (DestroyItem) ItemToRemove->MarkAsGarbage();
			if (OnItemRemoved.IsBound()) OnItemRemoved.Broadcast(ItemID, DestroyItem);
			UpdateGridWidget();
			return true;
		}
		else
		{
			int32 Remainder = AmmoundToRemove - ItemToRemove->GetCurrentAmmound();
			ItemToRemove->RemoveImmersiveItem();
			for (int32 i = 0; i < ItemSlots.Num(); i++)
			{
				if (ItemSlots[i] == ItemToRemove)
				{
					ItemSlots[i] = nullptr;
				}
			}
			UItemBase* RemainderItem = nullptr;
			for (UItemBase* LocalItem : ItemSlots)
			{
				if (LocalItem->GetClass() == ItemToRemove->GetClass())
				{
					RemoveItem(RemainderItem, Remainder, DestroyItem);
					if (OnItemRemoved.IsBound()) OnItemRemoved.Broadcast(ItemID, DestroyItem);
					UpdateGridWidget();
					return true;
				}
			}
		}
	}
	else
	{
		ItemToRemove->RemoveImmersiveItem();
		for (int32 i = 0; i < ItemSlots.Num(); i++)
		{
			if (ItemSlots[i] == ItemToRemove)
			{
				ItemSlots[i] = nullptr;
			}
		}
		if (DestroyItem) ItemToRemove->MarkAsGarbage();
		if (OnItemRemoved.IsBound()) OnItemRemoved.Broadcast(ItemID, DestroyItem);
		UpdateGridWidget();
		return true;
	}
	return false;
}

// This function don't needed in ABYSSWHISPER but i do this later for reflection engine inventory in other repo
bool UInventoryComponent::DropItem(UItemBase* ItemToRemove, int32 Ammound, bool DestroyAfterDrop)
{
	return false;
}

// This function don't needed in ABYSSWHISPER but i do this later for reflection engine inventory in other repo
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
	return true;
}

bool UInventoryComponent::UseItem(UItemBase* ItemToUse)
{
	if (IsValid(ItemToUse))
	{
		ItemToUse->StartUsingItem();
	}
	return true;
}

bool UInventoryComponent::IsRoomAvailable(UItemBase* ItemToAdd, int32 TopLeftIndex)
{
	/*if (!IsValid(ItemToAdd)) return false;*/
	FIntPoint ItemDimension = ItemToAdd->GetItemDimension();
	FItemTile StartTile = IndexToTile(TopLeftIndex);
	if (!IsTileValid(StartTile)) return false;
	if (StartTile.X + ItemDimension.X > ColumnSize || StartTile.Y + ItemDimension.Y > RowSize) return false;
	FItemTile Tile;
	for (int32 x = StartTile.X; x < ItemDimension.X + StartTile.X; x++)
	{
		for (int32 y = StartTile.Y; y < ItemDimension.Y + StartTile.Y; y++)
		{
			Tile = FItemTile(x, y);
			if (!IsTileValid(Tile)) return false;
			int32 Index = TileToIndex(Tile);
			if (IsValid(ItemSlots[Index])) return false;
			if (!ItemSlots.IsValidIndex(Index) || ItemSlots[Index] != nullptr) return false;
		}
	}
	return true;
}

bool UInventoryComponent::AddItemToSlot(UItemBase* ItemToAdd, int32 TopLeftIndex)
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
	if (OnItemAdded.IsBound()) OnItemAdded.Broadcast(ItemToAdd->GetItemSignature().ItemID);
	UpdateGridWidget();
	AddItemNotification(ItemToAdd, EInventoryAddingType::AddedToNew);
	return true;
}

void UInventoryComponent::AddItemAtClass(TSubclassOf<UItemBase> ItemClassToAdd, int32 AddedAmmound)
{
	UItemBase* LocalItem;
	if (IsValid(GetItemAtClass(ItemClassToAdd)))
	{
		LocalItem = GetItemAtClass(ItemClassToAdd);
		LocalItem->SetCurrentAmmound(LocalItem->GetCurrentAmmound() + AddedAmmound);
	}
	else
	{
		LocalItem = NewObject<UItemBase>(this, ItemClassToAdd);
		LocalItem->SetCurrentAmmound(AddedAmmound);
		AddItem(LocalItem);
	}
}

void UInventoryComponent::AddItemNotification(UItemBase* AddedItem, EInventoryAddingType ItemState)
{
	UpdateGridWidget();
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
					if (ItemToAdd->GetItemSignature().ItemID == ItemSlots[TileToIndex(FItemTile(x, y))]->GetItemSignature().ItemID && ItemSlots[TileToIndex(FItemTile(x, y))]->GetCurrentAmmound() < ItemSlots[TileToIndex(FItemTile(x, y))]->GetItemSignature().MaxStackSize)
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
	int32 MaxAmmound = CheckedSlot->GetItemSignature().MaxStackSize;
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

FItemTile UInventoryComponent::IndexToTile(int32 Index) const
{
	return FItemTile(Index % ColumnSize, Index / ColumnSize);
}

int32 UInventoryComponent::TileToIndex(FItemTile Tile) const
{
	int32 X = Tile.X;
	int32 Y = ColumnSize * Tile.Y;
	return X + Y;
}

UItemBase* UInventoryComponent::GetItemAtIndex(int32 ItemIndex) const
{
	return ItemSlots[ItemIndex];
}

TArray<UItemBase*> UInventoryComponent::GetAllItemSlots() const
{
	return ItemSlots;
}

TMap<UItemBase*, FItemTile> UInventoryComponent::GetAllItemsAndPosition() const
{
	TMap<UItemBase*, FItemTile> LocalItems;
	LocalItems.Empty();
	for (int32 i = 0; i < ItemSlots.Num(); i++)
	{
		if (IsValid(ItemSlots[i]))
		{
			if (!LocalItems.Contains(ItemSlots[i]))
			{
				LocalItems.Add(ItemSlots[i], IndexToTile(i));
			}
		}
	}
	return LocalItems;
}

UItemBase* UInventoryComponent::GetItemAtClass(TSubclassOf<UItemBase> SearchingClass) const
{
	for (UItemBase* LocalItem : ItemSlots)
	{
		if (!IsValid(LocalItem)) continue;
		if (LocalItem->GetClass() == SearchingClass)
		{
			return LocalItem;
		}
	}
	return nullptr;
}

int32 UInventoryComponent::GetItemAmmound(TSubclassOf<UItemBase> SearchingClass) const
{
	TArray<UItemBase*> ItemsAtClass;
	for (UItemBase* LocalItem : ItemSlots)
	{
		if (!IsValid(LocalItem)) continue;
		if (LocalItem->GetClass() == SearchingClass)
		{
			ItemsAtClass.Add(LocalItem);
		}
	}
	if (ItemsAtClass.IsEmpty()) return INDEX_NONE;
	int32 TotalAmmound = 0;
	for (int32 i = 0; i < ItemsAtClass.Num(); i++)
	{
		TotalAmmound += ItemsAtClass[i]->GetCurrentAmmound();
	}
	return TotalAmmound;
}

void UInventoryComponent::SetNewInventorySize(int32 Column, int32 Row)
{
	ColumnSize = Column;
	RowSize = Row;
	UpdateInventorySize();
}

EInventoryType UInventoryComponent::GetInventoryType() const
{
	return InventoryType;
}

FText UInventoryComponent::GetInventoryName() const
{
	return InventoryName;
}

float UInventoryComponent::GetItemTile() const
{
	return TileSize;
}

void UInventoryComponent::UpdateInventorySize()
{
	ItemSlots.SetNum(ColumnSize * RowSize);
	UpdateGridWidget();
}

void UInventoryComponent::CreateGridWidget()
{
	InventoryGrid = CreateWidget<UUserWidget>(GetWorld(), InventoryGridClass);
	IWidgetsInterface::Execute_SetOwnerInventoryReference((UObject*)InventoryGrid, this);
	UpdateGridWidget();
}

void UInventoryComponent::UpdateGridWidget()
{
	if (IsValid(InventoryGrid))
	{
		IWidgetsInterface::Execute_UpdateInventoryGrid((UObject*)InventoryGrid);
	}
}

void UInventoryComponent::GetWidgetClass()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> InventoryGridWidget(TEXT("/Game/SD/Systems/InventorySystem/UI/InventoryGrid"));
	if (InventoryGridWidget.Class != nullptr)
	{
		InventoryGridClass = InventoryGridWidget.Class;
		return;
	}
}

UUserWidget* UInventoryComponent::GetGridWidget() const
{
	return InventoryGrid;
}