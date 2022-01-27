#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "LevelPortalStructureCpp.generated.h"

USTRUCT(BlueprintType)
struct SUBJECT16_API FLevelPortalStructureCpp : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

  public:
    FLevelPortalStructureCpp() : OriginLevel({"None"}), DestinationLevel({"None"})
    {
    }

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Portal")
    FName OriginLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Portal")
    FName DestinationLevel;
};
