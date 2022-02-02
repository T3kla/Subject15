#include "PowerActivationComponent.h"
#include "Subject15Character.h"
#include "ProjectileActivation.h"
#include "Activator.h"

UPowerActivationComponent::UPowerActivationComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UPowerActivationComponent::ExecutePower()
{
    Super::ExecutePower();

    FVector A, B;
    FHitResult Res;
    Character->GetPistolShot(A, B, Res);

    auto Bullet = Cast<AProjectileActivation>(
        GetWorld()->SpawnActor<AProjectileBase>(this->ProjectilePowerType, A, (B - A).Rotation()));

    Bullet->ActivationCompCpp = this;
}

void UPowerActivationComponent::SetCurrentlyActive(AActivator *NewActive)
{
    CurrentlyActive = NewActive;
}

void UPowerActivationComponent::ResetCurrentlyActive()
{
    if (CurrentlyActive)
        CurrentlyActive->Deactivate();

    CurrentlyActive = nullptr;
}
