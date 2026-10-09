
<img width="2000" height="711" alt="ABYSSWHISPER TEXT LOGO" src="https://github.com/user-attachments/assets/20ac904c-b905-4c6d-bf96-0f745853c0a1" />

`ABYSSWHISPER INVENTORY SYSTEM`

Developed in Unreal Engine 5. "Unreal Engine" and its logo are trademarks or registered trademarks of Epic Games, Inc.

>[!IMPORTANT]
>Important! At the moment this system is not ready for integration into other projects; right now it is just a visual guide on how it can be done, and a demonstration of skills.
>If you just download this system now and insert it into your project, it will not work, because it is tied to the ABYSSWHISPER project.

**ENGLISH VERSION WILL BE LATER AND BELOW RUSSIAN**

## RUSSIAN README

# ABYSSWHISPER INVENTORY SYSTEM
The ABYSSWHISPER inventory system is the spiritual successor to the After Darkness inventory system, its improved and refactored version, additionally fully ported to C++.
Specifically, this repository is intended as a temporary portfolio, and at this stage of development the system, although fully modular, is primarily tailored strictly to ABYSSWHISPER.
However, later, if there is a need for it, I plan to fork this system into REFLECTION ENGINE.
Briefly about what served as the reference for this inventory. The main reference is the inventory of the game Alan Wake 2. All inventories of this kind are essentially the same, but the way (in my opinion) the inventory in AW2 interacted
with other systems and how it worked for the atmosphere there was my reference.

# FUTURE PLANS
1. All current tasks for the ABYSSWHISPER project are implemented

# UPDATE DESCRIPTION

`v. 1.1.3` - Bug fixes and performance improvements

`v. 1.1.2` - Added the int32 CharmInventorySize parameter to the inventory save structure, to save the sizes of the inventory with charms. Small update to UPlayerInventoryComponent - IsCharmEmpty rewritten with the appropriate Spythoona Code-Style

`v. 1.1.1` - Small fix to UPlayerInventoryComponent - fixed a bug where items of the same class could be added twice to the radial menu, thus for example bandages could occupy both slots for healing items. Removed the InventorySystem folder to remove unnecessary nesting

`v. 1.1.0` - The QuickAccess system was completely redone, since the game uses a radial menu instead of quick access slots; due to how item usage is structured, quick access cells are not suitable, a URadialMenu class was added as the base menu widget,
PlayerInventory was updated. The implementation in UWeaponItemBase was updated.

`v. 1.0.9` - The repository was split into 2 branches, the main one - where all innovations take place, and also the DefaultQuickAccess branch, with old-style quick access slots, inherited from After Darkness, inspired by Alan Wake 2.

`v. 1.0.8` - Added the UGeneratedLootDataAsset class - a child of ULootDataAsset, which generates loot itself, according to selected parameters: item type and "rarity" - a conditional parameter that the player will not see.

`v. 1.0.7` - Save structures moved into one file - InventorySave.h

`v. 1.0.6` - Bug fixes for Save/Load logic

`v. 1.0.5` - Simple weapon upgrading was implemented and UAttachmentItemBase was added - the base class for all weapon attachments.

`v. 1.0.4` - Small changes in UStashInventoryComponent

`v. 1.0.3` - Bug fixes.

`v. 1.0.2` - Stash Inventory now pulls the owner's name through the interface - cosmetics for the UI and the player.

`v. 1.0.1` - Fixed encoding

`v. 1.0.0` - The latest version of the inventory for ABYSSWHISPER. Almost all fatal problems have been solved. After that, only fixes for bugs that may accidentally come up, and also a fork for Reflection Engine, but that is later, someday...

`v. 0.0.20` - Bug fixes

`v. 0.0.19` - Bug fixes, expansion of UGarbageItemBase, addition of structures for crafting. Crafting is simple logic, it is implemented in blueprints.

`v. 0.0.18` - UHealthItemBase is almost finished - now the item can heal the player, but there are no animations yet, only numbers. Fixed a bug with adding items to the inventory if it is a new item or adding a stack.

`v. 0.0.17` - The InventoryComponent::UseItem method has been improved - after use, the item is deleted. AddImmersiveItem and RemoveImmersiveItem are now called only if it is the player's inventory. UItemBase - item logic has been redesigned, now there is no "explicit" use of items.

`v. 0.0.16` - Now the AddImmersive method is called in AddItem and AddItemToStack only if it is the player's inventory. Added a basic stub for the adaptive loot system.

`v. 0.0.15` - Methods for saving and loading have been added to the UInventoryComponent and UPlayerInventoryComponent classes.

`v. 0.0.14` - The UInventoryComponent::IsRoomAvailable method has been improved, fixed an error in calculating large items

`v. 0.0.13` - The UInventoryComponent::RemoveItem method has been completely redone - old errors fixed and the ability to remove an item with a remainder added - for example, if the amount to remove is 12, and the amount of the item being removed is 10, then the method will find a new item and remove the missing amount from it. Fixed the condition in adding resources (UPlayerInventoryComponent::AddResourceAtType)

`v. 0.0.12` - Added parent classes for various items: UGarbageItemBase, UHealthItemBase, UMiscellaneousItemBase, UQuestItemBase, UThrowableItemBase, UWeaponItemBase. Added two delegates to UInventoryComponent - for picking up an item and for throwing it away.

`v. 0.0.11` - Small fixes. Added UStashInventoryComponent classes - for special stashes, an inventory class intended for special loot boxes. Regular boxes will spawn items and "throw" them out, while this one will contain items without creating them in the world. Like, for example, in STALKER 2 how loot from enemies or stashes is implemented.
And UStorageInventoryComponent - an inventory class intended for storing items that the player does not need at the moment. Since the inventory itself is not self-sufficient, this type of component will be attached either to GameMode or to a special custom AftermathSystem. At the moment both classes are not ready, only the base implementation.

`v. 0.0.10` - UInventoryComponent updated - methods GetItemAmmound() and GetItemAtClass() implemented, method AddItemAtClass() added - the method implements adding an item when the calling class does not have or does not know a reference to UItemBase. Added class UAmmunitionItemBase - the base class for any type of ammunition in the game.

`v. 0.0.9` - Added UDevelopmentItemBase - the base class for items that will not be in the final version and are created for testing and debugging. This principle of operation helps to structure and organize dependencies. Small changes.

`v. 0.0.8` - UInventoryComponent updated, access to the ItemSignature and ItemDimension variables redesigned - now everything is done through getters, as was originally planned. AItemPickUp removed - its logic was moved to a blueprint analogue; it is a simple class and does not have to be in C++.
In UPlayerInventoryComponent, access to AHUD was added and a call for notifications about adding an item was added. The CharmsInventory subsystem was slightly improved - now it is fully ready and tested. Added class UCharmsItemBase - the base parent class for any charms, **if a charm is not inherited from this class, it cannot be added to CharmsInventory**. Small changes in the FItemSignature and FKeyDataSignature structures.

`v. 0.0.7` - Small fixes throughout the entire system, edits and improvements. Added a setup function in AItemPickUp, implemented using asynchronous asset loading, to improve project optimization.

`v. 0.0.6` - Added AItemPickUp - an actor with the help of which items will be represented in the world and will be added to and removed from the inventory.

`v. 0.0.5` - Several new functions were added to UItemBase for using elements and visual updates. Added UBatteryItemBase — the main element for battery items and setting default data for this hierarchy of child classes. Minor changes in UInvenotoryComponent.

`v. 0.0.4` - Added the Charms subsystem (Charm Slots) to UPlayerInventoryComponent.

`v .0.0.3` - Added the Key Items subsystem to UPlayerInventoryComponent and updated the Resources subsystem (KeyData Inventory & Resources).

`v. 0.0.2` - Added class UPlayerInventoryComponent, extending the logic of the base class and adding additional subsystems to the inventory, such as Resources, Charms, Quick Access and Key Items.

`v. 0.0.1` - Initial commit

# ABOUT REFLECTION ENGINE

Reflection Engine was mentioned several times in the text, and this brief reference describes what it is.
Reflection Engine is a modular framework for Unreal Engine 5, developed as a consolidated codebase of production-ready game systems. It serves several purposes:
Internal standardization: Provides a unified foundation for all SPYTHOONA INTERACTIVE projects, ensuring consistency and reducing development costs.
Technical portfolio: Acts as a visual representation of core engineering and architectural competencies in game systems design.
Commercial potential: Offers a base level for a potential future commercial product aimed at rapid prototyping and development of narrative and adventure genres.
The framework is built with an emphasis on modularity, data-driven design, and clean C++/Blueprint integration, which allows scaling and maintaining project development.

<img width="839" height="145" alt="Reflection Engine" src="https://github.com/user-attachments/assets/d4bd0d6a-16e5-48cc-a038-551a7b352c12" />

`A SPYTHOONA INTERACTIVE STORYTELLING TECHNOLOGY`
