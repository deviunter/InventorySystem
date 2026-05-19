// Copyright SPYTHOONA INTERACTIVE. All rights reserved. ABYSSWHISPER is a trademark of SPYTHOONA INTERACTIVE.
// Unreal Engine and its logo are trademarks or registered trademarks of Epic Games, Inc.
// in the United States and elsewhere.All other trademarks are the property of their respective owners.

#include "Systems/InventorySystem/UserInterface/RadialMenu.h"

void URadialMenu::UpdateMenu(float AxisX, float AxisY)
{
    /*float Length = FMath::Sqrt(AxisX * AxisX + AxisY * AxisY);
    if (Length < 0.2f) return;
    float Radians = FMath::Atan2(AxisY, AxisX);
    float Degrees = FMath::RadiansToDegrees(Radians);
    if (Degrees < 0.0f) Degrees += 360.0f;
    Degrees += 90.0f;
    if (Degrees >= 360.0f) Degrees -= 360.0f;
    float SectorAngle = 360.0f / SlotsCount;
    float HalfSector = SectorAngle * 0.5f;
    float Adjusted = Degrees + HalfSector;
    if (Adjusted >= 360.0f) Adjusted -= 360.0f;
    int32 Index = FMath::FloorToInt(Adjusted / SectorAngle);
    OnMenuUpdated(Index, SectorAngle);*/

    float Length = FMath::Sqrt(AxisX * AxisX + AxisY * AxisY);
    if (Length < 0.2f) return;

    FVector2D RawDir(AxisX, AxisY);
    float SmoothFactor = 0.1f;
    SmoothedDir = SmoothedDir * (1.0f - SmoothFactor) + RawDir * SmoothFactor;
    SmoothedDir.Normalize();

    float Radians = FMath::Atan2(SmoothedDir.Y, SmoothedDir.X);
    float Degrees = FMath::RadiansToDegrees(Radians);
    if (Degrees < 0.0f) Degrees += 360.0f;
    Degrees += 90.0f;
    if (Degrees >= 360.0f) Degrees -= 360.0f;
    float SectorAngle = 360.0f / SlotsCount;
    float HalfSector = SectorAngle * 0.5f;
    float Adjusted = Degrees + HalfSector;
    if (Adjusted >= 360.0f) Adjusted -= 360.0f;
    int32 Index = FMath::FloorToInt(Adjusted / SectorAngle);
    OnMenuUpdated(Index, SectorAngle);
}
