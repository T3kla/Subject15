#pragma once

#include "CoreMinimal.h"
#include "PowerBaseComponent.h"
#include "PowerActivationComponent.generated.h"

class AActivator;

UCLASS()
class SUBJECT16_API UPowerActivationComponent : public UPowerBaseComponent
{
    GENERATED_BODY()

  public:
    UPowerActivationComponent();

    virtual void ExecutePower() override;

    void SetCurrentlyActive(AActivator *NewActive);
    void ResetCurrentlyActive();

  protected:
    AActivator *CurrentlyActive;
};
