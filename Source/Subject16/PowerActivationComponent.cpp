#include "PowerActivationComponent.h"
#include "Subject15Character.h"

UPowerActivationComponent::UPowerActivationComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UPowerActivationComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UPowerActivationComponent::FirePressed()
{
    Super::FirePressed();
}

void UPowerActivationComponent::FireReleased()
{
    Super::FireReleased();
}

void UPowerActivationComponent::ActivatePower()
{
    Super::ActivatePower();
}

void UPowerActivationComponent::DeactivatePower()
{
    Super::DeactivatePower();
}

void UPowerActivationComponent::ExecutePower()
{
    Super::ExecutePower();

    FVector A, B;
    Character->GetPistolShot(A, B);

    auto projectile =
        GetWorld()->SpawnActor<AProjectileBase>(this->ProjectilePowerType, A, (B - A).Rotation());

    // projectile->GetProjectileMovementComponent()->Velocity = FVector::mag
}
