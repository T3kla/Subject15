#include "PowerBaseComponent.h"
#include "Subject15Character.h"
#include "Kismet/GameplayStatics.h"

UPowerBaseComponent::UPowerBaseComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	Character = Cast<ASubject15Character>(GetOwner());
}

void UPowerBaseComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPowerBaseComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPowerBaseComponent::FirePressed()
{
	if (IsInCooldown)
		return;

	switch (FireMode)
	{
	case EFireMode::Automatic:
		GetWorld()->GetTimerManager().SetTimer(
			AutomaticTimer, this, &UPowerBaseComponent::ExecutePower, FireRate, true, 0.f);
		SetCooldown();
		break;
	case EFireMode::Semiautomatic:
		ExecutePower();
		SetCooldown();
		break;
	case EFireMode::Laser:
		ExecutePower();
		SetCooldown();
		break;
	default:
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Red, "INVALID FireMode Selected!");
		break;
	}
}

void UPowerBaseComponent::FireReleased()
{
	if (FireMode == EFireMode::Automatic)
		GetWorld()->GetTimerManager().ClearTimer(AutomaticTimer);
}

void UPowerBaseComponent::ActivatePower()
{
	Character->SetPistolColor(PowerColor);
	//Character->OnPowerChange(PowerImg, PowerName);
}

void UPowerBaseComponent::DeactivatePower()
{
	FireReleased();
}

void UPowerBaseComponent::ExecutePower()
{
	if (FireMode == EFireMode::Automatic)
	{
		SetCooldown(-0.001f);
	}

	PlayPowerSound();
}

void UPowerBaseComponent::SetCooldown(float Modifier)
{
	IsInCooldown = true;
	GetWorld()->GetTimerManager().SetTimer(CooldownTimer, this, &UPowerBaseComponent::ResetCooldown,
		FireRate + Modifier, false);
}

void UPowerBaseComponent::ResetCooldown()
{
	IsInCooldown = false;
}

void UPowerBaseComponent::PlayPowerSound()
{
	
}