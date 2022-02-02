#include "ProjectileActivation.h"
#include "Activator.h"
#include "PowerActivationComponent.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"

AProjectileActivation::AProjectileActivation()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AProjectileActivation::BeginPlay()
{
    Super::BeginPlay();
}

void AProjectileActivation::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AProjectileActivation::DestroyProjectile()
{
    Super::DestroyProjectile();
}

void AProjectileActivation::OnOverlap(UPrimitiveComponent *OverlappedComp, AActor *Other,
                                      UPrimitiveComponent *OtherComp, int32 OtherBodyIndex,
                                      bool bFromSweep, const FHitResult &SweepResult)
{
    if (Other->ActorHasTag("Activator"))
    {
        auto *NewActive = Cast<AActivator>(Other);

        NewActive->Activate();

        if (ActivationCompCpp)
            ActivationCompCpp->SetCurrentlyActive(NewActive);
    }
    else
    {
        if (ActivationCompCpp)
            ActivationCompCpp->ResetCurrentlyActive();
    }

    DestroyProjectile();
}
