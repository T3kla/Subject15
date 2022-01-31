#pragma once

#include "CoreMinimal.h"
#include "PowerBaseComponent.h"
#include "PowerActivationComponent.generated.h"

UCLASS()
class SUBJECT16_API UPowerActivationComponent : public UPowerBaseComponent
{
    GENERATED_BODY()

  public:
    UPowerActivationComponent();

    virtual void FirePressed() override;
    virtual void FireReleased() override;
    virtual void ActivatePower() override;
    virtual void DeactivatePower() override;
    virtual void ExecutePower() override;

  protected:
    virtual void BeginPlay() override;
};
