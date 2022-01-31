#include "ProjectileActivation.h"

AProjectileActivation::AProjectileActivation()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AProjectileActivation::BeginPlay()
{
    Super::BeginPlay();

    // Bind to Box Collision
    SphereCompCpp->OnComponentBeginOverlap.AddDynamic(this, &AProjectileActivation::OnOverlap);
}

void AProjectileActivation::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AProjectileActivation::OnOverlap(UPrimitiveComponent *OverlappedComp, AActor *Other,
                                      UPrimitiveComponent *OtherComp, int32 OtherBodyIndex,
                                      bool bFromSweep, const FHitResult &SweepResult)
{
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Yellow, "asd");
    Destroy();
}