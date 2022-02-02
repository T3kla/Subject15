#include "PowerExplosionComponent.h"
#include "Subject15Character.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UPowerExplosionComponent::UPowerExplosionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UPowerExplosionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPowerExplosionComponent::FirePressed()
{
	Super::FirePressed();
}

void UPowerExplosionComponent::FireReleased()
{
	Super::FireReleased();
}

void UPowerExplosionComponent::ActivatePower()
{
	Super::ActivatePower();
}

void UPowerExplosionComponent::DeactivatePower()
{
	Super::DeactivatePower();
}

void UPowerExplosionComponent::ExecutePower()
{
	Super::ExecutePower();

	FVector A, B;
	FHitResult Res;
	Character->GetPistolShot(A, B, Res);

	FVector SoundLocation = Character->GetArrowComponent()->GetComponentTransform().GetLocation();
	UGameplayStatics::PlaySoundAtLocation(this, PowerSoundFX, SoundLocation 
	/*, float VolumeMultiplier = 1.f, float PitchMultiplier = 1.f, 
	float StartTime = 0.f, class USoundAttenuation* AttenuationSettings = nullptr, 
	USoundConcurrency * ConcurrencySettings = nullptr*/);

	GetWorld()->SpawnActor<AProjectileBase>(this->ProjectilePowerType, A, (B - A).Rotation());
}