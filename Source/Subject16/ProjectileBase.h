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
    virtual void BeginPlay() override;
};
