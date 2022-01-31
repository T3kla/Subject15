#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "ProjectileActivation.generated.h"

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
    void OnOverlap(UPrimitiveComponent *OverlappedComp, AActor *Other,
                   UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                   const FHitResult &SweepResult);
};
