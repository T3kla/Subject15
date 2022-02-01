#include "Activator.h"

AActivator::AActivator()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AActivator::BeginPlay()
{
    Super::BeginPlay();
}

void AActivator::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AActivator::Activate()
{
}

void AActivator::Deactivate()
{
}