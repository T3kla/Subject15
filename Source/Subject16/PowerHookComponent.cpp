#include "PowerHookComponent.h"
#include "Subject15Character.h"

UPowerHookComponent::UPowerHookComponent()
{
    PrimaryComponentTick.bCanEverTick = true;

    CanGrapple = true;
    HookLocation = {0.f, 0.f, 0.f};
}

void UPowerHookComponent::BeginPlay()
{
    Super::BeginPlay();

    uParticleSystem = Character->PistolParticleSystem;
    uArrowComponent = Character->PistolMuzzleCompCpp;
    ResetGrappleHook();
}

void UPowerHookComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (uParticleSystem->IsVisible())
        ShowHook();
}

void UPowerHookComponent::ShootGrappleHook()
{
    uParticleSystem->SetVisibility(true);

    uParticleSystem->SetBeamSourcePoint(0, uArrowComponent->GetComponentLocation(), 0);
    uParticleSystem->SetBeamTargetPoint(0, HookLocation, 0);
}

void UPowerHookComponent::ResetGrappleHook()
{
    uParticleSystem->SetVisibility(false);
    CanGrapple = true;
}

void UPowerHookComponent::LaunchCharacter(FVector &Velocity, bool Override)
{
    Character->LaunchCharacter(Velocity, Override, Override);
}

void UPowerHookComponent::LaunchCharacterForce()
{
    FVector Velocity = (HookLocation - Character->GetActorLocation()) * 1.5f;
    LaunchCharacter(Velocity, false);
}

void UPowerHookComponent::ShowHook()
{
    if (uParticleSystem && uArrowComponent)
    {
        uParticleSystem->SetBeamSourcePoint(0, uArrowComponent->GetComponentLocation(), 0);
        uParticleSystem->SetBeamTargetPoint(0, HookLocation, 0);
    }
}

void UPowerHookComponent::ExecutePower()
{
    FVector A, B, InitForce(0, 0, 500);
    FHitResult Res;
    FTimerHandle TimerHandleInit, TimerHandleForce;

    if (Character->GetCameraShot(A, B, Res))
    {
        HookLocation = B;
        ShootGrappleHook();
        LaunchCharacter(InitForce, true);

        GetWorld()->GetTimerManager().SetTimer(
            TimerHandleInit, this, &UPowerHookComponent::LaunchCharacterForce, 0.2f, false);
        GetWorld()->GetTimerManager().SetTimer(TimerHandleForce, this,
                                               &UPowerHookComponent::ResetGrappleHook, 0.5f, false);
    }
    else
        ResetGrappleHook();
}

void UPowerHookComponent::ActivatePower()
{
    Character->PistolParticleSystem->SetTemplate(TemplateParticle);
    Character->SetPistolColor(PowerColor);
}
