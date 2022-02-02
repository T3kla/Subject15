#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ProjectileBase.generated.h"

UCLASS()
class SUBJECT16_API AProjectileBase : public AActor
{
    GENERATED_BODY()

  public:
    AProjectileBase();

    virtual void Tick(float DeltaTime) override;

    const UProjectileMovementComponent *GetProjectileMovementComponent();

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    USphereComponent *SphereCompCpp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    UProjectileMovementComponent *ProjectileMovementCompCpp;

  protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float Lifetime = 2.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USoundBase *ProjectileSoundFX;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    UParticleSystem *ProjectileExplosionVFX;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FVector ExplosionScale = {.6f, .6f, .6f};

  protected:
    virtual void BeginPlay() override;

    virtual void OnOverlap(UPrimitiveComponent *OverlappedComp, AActor *Other,
                           UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                           const FHitResult &SweepResult);

    virtual void DestroyProjectile();

    virtual void PlayProjectileExplosionSFX();

    virtual void PlayProjectileExplosionVFX();
};
