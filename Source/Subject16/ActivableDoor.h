#pragma once

#include "CoreMinimal.h"
#include "Activable.h"
#include "ActivableDoor.generated.h"

class ATargetPoint;

UCLASS()
class SUBJECT16_API AActivableDoor : public AActivable
{
    GENERATED_BODY()

  public:
    AActivableDoor();

    UPROPERTY(VisibleInstanceOnly)
    bool IsActive;

    UPROPERTY(EditInstanceOnly)
    ATargetPoint *InitialPosition;

    UPROPERTY(EditInstanceOnly)
    ATargetPoint *FinalPosition;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float Speed;

  private:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void Activate() override;
    virtual void Deactivate() override;

    FVector InitPos = {0.f, 0.f, 0.f};
    FVector FinalPos = {0.f, 0.f, 0.f};
    float Progress = 0.f;
};
