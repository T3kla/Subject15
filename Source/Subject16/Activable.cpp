#include "Activable.h"

AActivable::AActivable()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AActivable::BeginPlay()
{
    Super::BeginPlay();
}

void AActivable::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AActivable::Activate()
{
}

void AActivable::Deactivate()
{
}