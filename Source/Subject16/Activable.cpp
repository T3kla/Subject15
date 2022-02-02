#include "Activable.h"

AActivable::AActivable()
{
    PrimaryActorTick.bCanEverTick = false;

    RootCompCpp = CreateDefaultSubobject<USceneComponent>(TEXT("RootCompCpp"));
    SetRootComponent(RootCompCpp);
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