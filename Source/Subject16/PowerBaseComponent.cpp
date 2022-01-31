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
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Cyan, "PowerBase FirePressed");

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
        if (GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Red, "INVALID FireMode Selected!");
    }
}

void UPowerBaseComponent::FireReleased()
{
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Cyan, "PowerBase FireReleased");

    GetWorld()->GetTimerManager().ClearTimer(*FireTimerHandle);
}

void UPowerBaseComponent::ActivatePower()
{
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Cyan, "PowerBase ActivatePower");

    Character->SetPistolColor(PowerColor);
}

void UPowerBaseComponent::DeactivatePower()
{
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Cyan, "PowerBase DeactivatePower");

    GetWorld()->GetTimerManager().ClearTimer(*FireTimerHandle);
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
    // FirePointTransform.GetLocation(),
    //                                          CameraPitchRotator);

    // if (GEngine)
    // {
    //     GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, TEXT("LLEGO Fire Power!\n"));
    // }
}
