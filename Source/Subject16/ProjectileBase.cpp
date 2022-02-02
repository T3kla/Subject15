#include "ProjectileBase.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"

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

    // Bind to Box Collision
    SphereCompCpp->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBase::OnOverlap);

    // Lifetime
    FTimerHandle LifetimeTimer;
    GetWorld()->GetTimerManager().SetTimer(
        LifetimeTimer, this, &AProjectileBase::DestroyProjectile, Lifetime, false);
}

void AProjectileBase::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    DestroyProjectile();
}

void AProjectileBase::DestroyProjectile()
{
    PlayProjectileExplosionSFX(); //Sound
    PlayProjectileExplosionVFX(); //VFX

    Super::Destroy();
}


void AProjectileBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

const UProjectileMovementComponent *AProjectileBase::GetProjectileMovementComponent()
{
    return ProjectileMovementCompCpp;
}

//Effects when Projectile Collision
void AProjectileBase::PlayProjectileExplosionSFX()
{
    if (ProjectileSoundFX)
    {
        FVector SoundLocation = GetActorLocation();

        UGameplayStatics::PlaySoundAtLocation(this, ProjectileSoundFX, SoundLocation);
    }
    else {
        if (GEngine) {

            GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Yellow,
                "You MUST include a SoundFX to this Projectile!");
        }
    }
}

void AProjectileBase::PlayProjectileExplosionVFX()
{
    if (ProjectileExplosionVFX)
    {

    // Spawn Explosion
    FTransform VFXTransform(GetActorRotation(), GetActorLocation(), ExplosionScale);
    
    UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ProjectileExplosionVFX, VFXTransform, true,
        EPSCPoolMethod::AutoRelease, true);
    }
    else
    {
        if (GEngine) {

            GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Yellow,
                "You MUST include a ExplosionVFX-(ParticleSystem)- to this Power!");
        }
    }
}