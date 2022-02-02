#pragma once

#include "CoreMinimal.h" //Ya la tiene el ProjectileBase.h
#include "ProjectileBase.h"
#include "ProjectileActivation.generated.h"

class UParticleSystem;

UCLASS()
class SUBJECT16_API AProjectileActivation : public AProjectileBase
{
    GENERATED_BODY()

  public:
    AProjectileActivation();

    virtual void Tick(float DeltaTime) override;

  protected:
    virtual void BeginPlay() override;

  private:
    UFUNCTION()
    virtual void OnOverlap(UPrimitiveComponent *OverlappedComp, AActor *Other,
                   UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                   const FHitResult &SweepResult) override;

protected:
    virtual void DestroyProjectile() override;
};
