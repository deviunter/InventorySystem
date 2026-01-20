// © 2025 Skydream Interactive. All rights reserved. ABYSSWHISPER™ is a trademark of Skydream Interactive.
// Unreal® Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere. All other trademarks are the property of their respective owners.

// Reflection Engine © 2025 Deviunter & Skydream Interactive. All Rights Reserved. 
// This software and its source code are the intellectual property of Skydream Interactive.
// Unauthorized copying, modification, distribution, or use is strictly prohibited.

#include "Systems/InventorySystem/Classes/PlayerInventoryComponent.h"

UPlayerInventoryComponent::UPlayerInventoryComponent()
{
	// SET UP RESOURCE ARRAY
	ResourceList.Empty();
	ResourceList.Add(FResourceSignature(0, 20, EResourceType::WoodResource));
	ResourceList.Add(FResourceSignature(0, 30, EResourceType::MetalResource));
	ResourceList.Add(FResourceSignature(0, 15, EResourceType::ElectricalResource));
	ResourceList.Add(FResourceSignature(0, 35, EResourceType::ChemicalResource));
	ResourceList.Add(FResourceSignature(0, 35, EResourceType::BioResource));
}

EResourceAddType UPlayerInventoryComponent::AddResouceAtType(EResourceType ResourceType, int32 AddAmmound)
{
	for (int32 i = 0; i < ResourceList.Num(); i++)
	{
		if (ResourceList[i].ResourceType == ResourceType)
		{
			if (ResourceList[i].MaxAmmound + AddAmmound <= ResourceList[i].MaxAmmound)
			{
				ResourceList[i].CurrentAmmound += AddAmmound;
				return EResourceAddType::Success;
			}
			else
			{
				ResourceList[i].CurrentAmmound = ResourceList[i].MaxAmmound;
				return EResourceAddType::Partition;
			}
		}
	}
	return EResourceAddType::Fail;
}

FResourceSignature UPlayerInventoryComponent::GetResourceAtType(EResourceType ResourceType)
{
	for (int32 i = 0; i < ResourceList.Num(); i++)
	{
		if (ResourceList[i].ResourceType == ResourceType)
		{
			return ResourceList[i];
		}
	}
	return FResourceSignature();
}
