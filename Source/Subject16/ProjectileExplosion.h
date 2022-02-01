#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "ProjectileExplosion.generated.h"

class UParticleSystem;

UCLASS()
class SUBJECT16_API AProjectileExplosion : public AProjectileBase
{
	GENERATED_BODY()

public:
	AProjectileExplosion();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UParticleSystem* ParticleSys;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FVector ParticleSize = { .2f, .2f, .2f };

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float Lifetime = 2.f;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);
		void DestroyProjectile();
};
