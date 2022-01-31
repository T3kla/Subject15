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

  protected:
    virtual void BeginPlay() override;

  public:
  private:
  protected:
};
