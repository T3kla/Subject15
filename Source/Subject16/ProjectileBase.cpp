#include "ProjectileBase.h"

AProjectileBase::AProjectileBase()
{
    PrimaryActorTick.bCanEverTick = true;

    SphereCompCpp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCompCpp"));
    SetRootComponent(SphereCompCpp);

    ProjectileMovementCompCpp =
        CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementCompCpp"));
    ProjectileMovementCompCpp->SetUpdatedComponent(SphereCompCpp);
}

void AProjectileBase::BeginPlay()
{
    Super::BeginPlay();
}

void AProjectileBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

const UProjectileMovementComponent *AProjectileBase::GetProjectileMovementComponent()
{
    return ProjectileMovementCompCpp;
}
