#include "Activator.h"

AActivator::AActivator()
{
    PrimaryActorTick.bCanEverTick = false;

    RootCompCpp = CreateDefaultSubobject<USceneComponent>(TEXT("RootCompCpp"));
    SetRootComponent(RootCompCpp);
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
    IsActive = true;

    for (auto &&Activable : ActivablesArray)
        Activable->Activate();
}

void AActivator::Deactivate()
{
    IsActive = false;

    for (auto &&Activable : ActivablesArray)
        Activable->Deactivate();
}