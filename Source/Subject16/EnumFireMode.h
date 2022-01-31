#pragma once

UENUM()
enum class EFireMode : uint8
{
    None = 0 UMETA(DisplayName = "None"),
    Default = 1 UMETA(DisplayName = "Default"),
    Semiautomatic = 2 UMETA(DisplayName = "Semiautomatic"),
    Automatic = 3 UMETA(DisplayName = "Automatic"),
    Laser = 4 UMETA(DisplayName = "Laser")
};