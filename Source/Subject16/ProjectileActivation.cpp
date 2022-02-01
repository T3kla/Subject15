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

    // Lifetime
    FTimerHandle LifetimeTimer;
    GetWorld()->GetTimerManager().SetTimer(LifetimeTimer, this, &AProjectileActivation::Destroy,
                                           Lifetime, false);
}

void AProjectileActivation::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AProjectileActivation::Destroy()
{
    Super::Destroy();
}

void AProjectileActivation::OnOverlap(UPrimitiveComponent *OverlappedComp, AActor *Other,
                                      UPrimitiveComponent *OtherComp, int32 OtherBodyIndex,
                                      bool bFromSweep, const FHitResult &SweepResult)
{
    Destroy();
}
