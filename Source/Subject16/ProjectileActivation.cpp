#include "ProjectileActivation.h"

AProjectileActivation::AProjectileActivation()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AProjectileActivation::BeginPlay()
{
    Super::BeginPlay();
}

void AProjectileActivation::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
