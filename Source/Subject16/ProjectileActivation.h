#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "ProjectileActivation.generated.h"

class UParticleSystem;
class UPowerActivationComponent;

UCLASS()
class SUBJECT16_API AProjectileActivation : public AProjectileBase
{
    GENERATED_BODY()

  public:
    AProjectileActivation();

    UPowerActivationComponent *ActivationCompCpp;

  protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void DestroyProjectile() override;

  private:
    UFUNCTION()
    virtual void OnOverlap(UPrimitiveComponent *OverlappedComp, AActor *Other,
                           UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                           const FHitResult &SweepResult) override;
};
