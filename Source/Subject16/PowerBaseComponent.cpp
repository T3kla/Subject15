#include "PowerBaseComponent.h"
#include "Subject15Character.h"

UPowerBaseComponent::UPowerBaseComponent()
{
    PrimaryComponentTick.bCanEverTick = true;

    Character = Cast<ASubject15Character>(GetOwner());
}

void UPowerBaseComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UPowerBaseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPowerBaseComponent::FirePressed()
{
    if (FireMode == EFireMode::Automatic)
    {
        GetWorld()->GetTimerManager().SetTimer(
            FireTimerHandle, this, &UPowerBaseComponent::ExecutePower, 1 / FireRate, true, 0);
    }
    else if (FireMode == EFireMode::Semiautomatic)
    {
        ExecutePower();
    }
    else if (FireMode == EFireMode::Laser)
    {
        ExecutePower();
    }
    else
    {
        if (GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Red, "INVALID FireMode Selected!");
    }
}

void UPowerBaseComponent::FireReleased()
{
    GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
}

void UPowerBaseComponent::ActivatePower()
{
    Character->SetPistolColor(PowerColor);
}

void UPowerBaseComponent::DeactivatePower()
{
    GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
}

void UPowerBaseComponent::ExecutePower()
{
}
