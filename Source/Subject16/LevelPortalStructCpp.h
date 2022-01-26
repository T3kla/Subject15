#pragma once

#include "Engine/DataTable.h"
#include "UObject/NameTypes.h"
#include "LevelPortalStructCpp.generated.h"

USTRUCT(BlueprintType)
struct SUBJECT16_API FLevelPortalStructCpp : public FTableRowBase
{
    GENERATED_BODY()

  public:
    FLevelPortalStructCpp()
    {
        OriginLevel = TEXT("None");
        DestinationLevel = TEXT("None");
    }

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName OriginLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName DestinationLevel;
};
