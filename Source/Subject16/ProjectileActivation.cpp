#include "ProjectileActivation.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"

AProjectileActivation::AProjectileActivation()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AProjectileActivation::BeginPlay()
{
    Super::BeginPlay();

    // Bind to Box Collision
    SphereCompCpp->OnComponentBeginOverlap.AddDynamic(this, &AProjectileActivation::OnOverlap);

    // Lifetime
    FTimerHandle LifetimeTimer;
    GetWorld()->GetTimerManager().SetTimer(
        LifetimeTimer, this, &AProjectileActivation::DestroyProjectile, Lifetime, false);
}

void AProjectileActivation::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AProjectileActivation::DestroyProjectile()
{
    // Spawn Explosion
    FTransform Transform(GetActorRotation(), GetActorLocation(), ExplosionScale);
    UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion, Transform, true,
                                             EPSCPoolMethod::AutoRelease, true);

    // AActor Destroy
    Super::Destroy();
}

void AProjectileActivation::OnOverlap(UPrimitiveComponent *OverlappedComp, AActor *Other,
                                      UPrimitiveComponent *OtherComp, int32 OtherBodyIndex,
                                      bool bFromSweep, const FHitResult &SweepResult)
{
    if (Other->ActorHasTag("Activatable"))
    {
        if (GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Purple, "Activatable!");
    }

    DestroyProjectile();
}
