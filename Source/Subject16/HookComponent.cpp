#include "HookComponent.h"
#include "Subject15Character.h"
#include "Components/ArrowComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

UHookComponent::UHookComponent()
{
    CanGrapple = true;
    HookLocation = FVector(0, 0, 0);
}

void UHookComponent::BeginPlay()
{
    Super::BeginPlay();

    uParticleSystem = Character->PistolParticleSystem;
    uArrowComponent = Character->PistolMuzzleCompCpp;
    ResetGrappleHook();
}

void UHookComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                   FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (uParticleSystem->IsVisible())
        ShowHook();
}

void UHookComponent::ShootGrappleHook()
{
    uParticleSystem->SetVisibility(true);
    uParticleSystem->SetBeamSourcePoint(0, uArrowComponent->GetComponentLocation(), 0);
    uParticleSystem->SetBeamTargetPoint(0, HookLocation, 0);
}

void UHookComponent::ResetGrappleHook()
{
    uParticleSystem->SetVisibility(false);
    CanGrapple = true;
}

void UHookComponent::LaunchTowardsHook()
{
    FVector Velocity = (HookLocation - Character->GetActorLocation()) * 1.5f;
    Character->LaunchCharacter(Velocity, false, false);
}

void UHookComponent::ShowHook()
{
    if (uParticleSystem && uArrowComponent)
    {
        uParticleSystem->SetBeamSourcePoint(0, uArrowComponent->GetComponentLocation(), 0);
        uParticleSystem->SetBeamTargetPoint(0, HookLocation, 0);
    }
}

void UHookComponent::ExecutePower()
{
    FVector A, B, InitForce(0, 0, 500);
    FHitResult Res;
    FTimerHandle TimerHandleInit, TimerHandleForce;

    if (Character->GetCameraShot(A, B, Res))
    {
        HookLocation = B;
        ShootGrappleHook();
        Character->LaunchCharacter(InitForce, true, true);

        auto &TM = GetWorld()->GetTimerManager();
        TM.SetTimer(TimerHandleInit, this, &UHookComponent::LaunchTowardsHook, 0.2f, false);
        TM.SetTimer(TimerHandleForce, this, &UHookComponent::ResetGrappleHook, 0.5f, false);
    }
    else
    {
        ResetGrappleHook();
    }
}
