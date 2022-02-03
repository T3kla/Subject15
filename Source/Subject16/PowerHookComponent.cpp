#include "PowerHookComponent.h"
#include "Subject15Character.h"
#include "Kismet/GameplayStatics.h"

UPowerHookComponent::UPowerHookComponent()
{
    PrimaryComponentTick.bCanEverTick = true;

    CanGrapple = true;
    HookLocation = {0.f, 0.f, 0.f};
}

void UPowerHookComponent::BeginPlay()
{
    Super::BeginPlay();

    ParticleSystem = Character->PistolParticleSystem;
    PistolMuzzle = Character->PistolMuzzleCompCpp;
    ResetGrappleHook();
}

void UPowerHookComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (ParticleSystem->IsVisible())
        ShowHook();
}

void UPowerHookComponent::ShootGrappleHook()
{
    ParticleSystem->SetVisibility(true);

    ParticleSystem->SetBeamSourcePoint(0, PistolMuzzle->GetComponentLocation(), 0);
    ParticleSystem->SetBeamTargetPoint(0, HookLocation, 0);
}

void UPowerHookComponent::ResetGrappleHook()
{
    ParticleSystem->SetVisibility(false);
    CanGrapple = true;
}

void UPowerHookComponent::LaunchCharacter(FVector &Velocity, bool Override)
{
    Character->LaunchCharacter(Velocity, Override, Override);
}

void UPowerHookComponent::LaunchCharacterForce()
{
    FVector Velocity = (HookLocation - Character->GetActorLocation()) * 2.0f;
    LaunchCharacter(Velocity, false);
}

void UPowerHookComponent::ShowHook()
{
    if (ParticleSystem && PistolMuzzle)
    {
        ParticleSystem->SetBeamSourcePoint(0, PistolMuzzle->GetComponentLocation(), 0);
        ParticleSystem->SetBeamTargetPoint(0, HookLocation, 0);
    }
}

void UPowerHookComponent::ExecutePower()
{
    FVector A, B, InitForce(0, 0, 500);
    FHitResult Res;
    FTimerHandle TimerHandleInit, TimerHandleForce;

    if (Character->GetCameraShot(A, B, Res))
    {
        if (Res.Component->ComponentHasTag("HookEvent"))
        {
            HookLocation = B;
            ShootGrappleHook();
            LaunchCharacter(InitForce, true);

            GetWorld()->GetTimerManager().SetTimer(
                TimerHandleInit, this, &UPowerHookComponent::LaunchCharacterForce, 0.2f, false);
            GetWorld()->GetTimerManager().SetTimer(
                TimerHandleForce, this, &UPowerHookComponent::ResetGrappleHook, 0.5f, false);

            FVector SoundLocation = Character->GetActorLocation();
            UGameplayStatics::PlaySoundAtLocation(this, PowerSoundFX, SoundLocation);
        }
    }
    else
        ResetGrappleHook();
}

void UPowerHookComponent::ActivatePower()
{
    Character->PistolParticleSystem->SetTemplate(TemplateParticle);
    Character->SetPistolColor(PowerColor);
}
