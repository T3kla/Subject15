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

<<<<<<< Updated upstream
void UPowerBaseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
=======
void UPowerBaseComponent::TickComponent(float DeltaTime, ELevelTick TickType,
FActorComponentTickFunction *ThisTickFunction)
>>>>>>> Stashed changes
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPowerBaseComponent::FirePressed()
{
<<<<<<< Updated upstream
    if (FireMode == EFireMode::Automatic)
    {
        GetWorld()->GetTimerManager().SetTimer(
            *FireTimerHandle, this, &UPowerBaseComponent::ExecutePower, 1 / FireRate, true, 0);
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
=======
    switch (FireMode) {
    case EFireMode::Automatic:
        if (!IsInCooldown)
        {
            GetWorld()->GetTimerManager().SetTimer(
                AutomaticTimer, this, &UPowerBaseComponent::ExecutePower, FireRate, true, 0.f);
            SetCooldown();
        }
        break;
    case EFireMode::Semiautomatic:
        if (!IsInCooldown)
        {
            ExecutePower();
            SetCooldown();
        }
        break;
    case EFireMode::Laser:
        if (!IsInCooldown)
        {
            ExecutePower();
            SetCooldown();
        }
        break;
    default:
>>>>>>> Stashed changes
        if (GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Red, "INVALID FireMode Selected!");
    }
}

void UPowerBaseComponent::FireReleased()
{
    GetWorld()->GetTimerManager().ClearTimer(*FireTimerHandle);
}

void UPowerBaseComponent::ActivatePower()
{
    Character->SetPistolColor(PowerColor);
}

void UPowerBaseComponent::DeactivatePower()
{
<<<<<<< Updated upstream
    GetWorld()->GetTimerManager().ClearTimer(*FireTimerHandle);
=======

>>>>>>> Stashed changes
}

void UPowerBaseComponent::ExecutePower()
{
    // FVector a, b;
    // Character->GetPistolShot(a, b);

    // // SetUp the FirePoint and the Direction
    // FirePointTransform = Character->ArrowCompCpp->GetComponentTransform();

    // CameraPitchRotator =
    //     Cast<ASubject15Character>(GetOwner())->ArrowCompCpp->GetForwardVector().Rotation();

    // GetWorld()->SpawnActor<AProjectileClass>(ProjectilePowerType,
    // FirePointTransform.GetLocation(), CameraPitchRotator);

    // if (GEngine)
    // {
    //     GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, TEXT("LLEGO Fire Power!\n"));
    // }
}
