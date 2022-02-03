#include "ProjectileExplosion.h"
#include "particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"

AProjectileExplosion::AProjectileExplosion()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AProjectileExplosion::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectileExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectileExplosion::DestroyProjectile()
{
	Super::DestroyProjectile();
}

void AProjectileExplosion::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (Other->ActorHasTag("ExplosionEvent"))
	{
		Other->Destroy();
	}
	
	DestroyProjectile();
}