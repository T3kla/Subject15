#pragma once

UENUM()
enum class EPowers : uint8
{
    None = 0 UMETA(DisplayName = "None"),
    Default = 1 UMETA(DisplayName = "Default"),
    PushPull = 2 UMETA(DisplayName = "PushPull"),
    Activation = 3 UMETA(DisplayName = "Activation"),
    Explosion = 4 UMETA(DisplayName = "Explosion"),
    Hook = 5 UMETA(DisplayName = "Hook"),
    Phase = 6 UMETA(DisplayName = "Phase")
};
