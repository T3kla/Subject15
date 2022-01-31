#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PowersEnum.h"
#include "Engine/Texture2D.h"
#include "PowerStructure.generated.h"

USTRUCT(BlueprintType)
struct SUBJECT16_API FPowerStructure : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

  public:
    FPowerStructure()
    {
        Power = EPowers::None;
        Color = {0, 0, 0, 0};
    }

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power Structure")
    EPowers Power;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power Structure")
    FColor Color;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power Structure")
    UTexture2D *Texture;
};
