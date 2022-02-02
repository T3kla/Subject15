#pragma once

#include "Components/ArrowComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "CoreMinimal.h"
#include "PowerBaseComponent.h"
#include "PowerHookComponent.generated.h"

UCLASS()
class SUBJECT16_API UPowerHookComponent : public UPowerBaseComponent
{
    GENERATED_BODY()

  public:
    UPowerHookComponent();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UParticleSystem *TemplateParticle;

    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType,
                               FActorComponentTickFunction *ThisTickFunction) override;

    virtual void ActivatePower() override;
    virtual void ExecutePower() override;

    void ShootGrappleHook();
    void ResetGrappleHook();
    void LaunchCharacter(FVector &Velocity, bool Override);
    void LaunchCharacterForce();
    void ShowHook();

  protected:
    virtual void BeginPlay() override;

  private:
    UParticleSystemComponent *ParticleSystem;
    UArrowComponent *PistolMuzzle;

    bool CanGrapple;
    FVector HookLocation;
};
