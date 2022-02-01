#include "PowerExplosionComponent.h"
#include "Subject15Character.h"

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
	Character->GetPistolShot(A, B);

	auto projectile =
		GetWorld()->SpawnActor<AProjectileBase>(this->ProjectilePowerType, A, (B - A).Rotation());
	


}