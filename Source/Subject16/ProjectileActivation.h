#pragma once

#include "CoreMinimal.h"
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

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    UParticleSystem *Explosion;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FVector ExplosionScale = {.6f, .6f, .6f};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float Lifetime = 2.f;

  protected:
    virtual void BeginPlay() override;

  private:
    UFUNCTION()
    void OnOverlap(UPrimitiveComponent *OverlappedComp, AActor *Other,
                   UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                   const FHitResult &SweepResult);

    void DestroyProjectile();
};
