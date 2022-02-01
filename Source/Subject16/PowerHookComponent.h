#pragma once

#include "CoreMinimal.h"
#include "PowerBaseComponent.h"
#include "PowerHookComponent.generated.h"

class UParticleSystemComponent;
class UArrowComponent;

UCLASS()
class SUBJECT16_API UPowerHookComponent : public UPowerBaseComponent
{
    GENERATED_BODY()

  public:
    UPowerHookComponent();

    UFUNCTION()
    void ShootGrappleHook();

    UFUNCTION()
    void ResetGrappleHook();

    UFUNCTION()
    void LaunchCharacter(FVector &Velocity, bool Override);

    UFUNCTION()
    void LaunchCharacterForce();

    UFUNCTION()
    void ShowHook();

    UPROPERTY()
    UParticleSystemComponent *uParticleSystem;

    UPROPERTY()
    UArrowComponent *uArrowComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UParticleSystem *TemplateParticle;

    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType,
                               FActorComponentTickFunction *ThisTickFunction) override;
    virtual void ExecutePower() override;
    virtual void ActivatePower() override;

  protected:
    virtual void BeginPlay() override;

  private:
    bool CanGrapple;
    FVector HookLocation;
};
