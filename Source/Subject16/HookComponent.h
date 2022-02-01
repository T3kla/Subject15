#pragma once

#include "CoreMinimal.h"
#include "PowerBaseComponent.h"
#include "HookComponent.generated.h"

class UParticleSystemComponent;
class UArrowComponent;

UCLASS()
class SUBJECT16_API UHookComponent : public UPowerBaseComponent
{
    GENERATED_BODY()

  public:
    UHookComponent();

    UFUNCTION()
    void ShootGrappleHook();

    UFUNCTION()
    void ResetGrappleHook();

    UFUNCTION()
    void LaunchTowardsHook();

    UFUNCTION()
    void ShowHook();

    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType,
                               FActorComponentTickFunction *ThisTickFunction) override;

    virtual void ExecutePower() override;

    UPROPERTY()
    UParticleSystemComponent *uParticleSystem;

    UPROPERTY()
    UArrowComponent *uArrowComponent;

  protected:
    virtual void BeginPlay() override;

  private:
    bool CanGrapple;
    FVector HookLocation;
};
