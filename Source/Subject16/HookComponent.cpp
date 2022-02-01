// Fill out your copyright notice in the Description page of Project Settings.

#include "HookComponent.h"
#include "Subject15Character.h"
#include "Kismet/GameplayStatics.h"

/*Init values*/
UHookComponent::UHookComponent() 
{
		m_canGrappleHook = true;
		m_hookLocation = FVector(0, 0, 0);
}

void UHookComponent::ShootGrappleHook()
{
		uParticleSystem->SetVisibility(true);

		uParticleSystem->SetBeamSourcePoint(0, uArrowComponent->GetComponentLocation(), 0);
		uParticleSystem->SetBeamTargetPoint(0, m_hookLocation, 0);
}

void UHookComponent::ResetGrappleHook() 
{
		uParticleSystem->SetVisibility(false);
		m_canGrappleHook = true;
}

void UHookComponent::LaunchCharacter(FVector &Velocity, bool Override)
{
		Character->LaunchCharacter(Velocity, Override, Override);
}

void UHookComponent::LaunchCharacterForce()
{
		FVector Velocity = (m_hookLocation - Character->GetActorLocation()) * 1.5f;
		LaunchCharacter(Velocity, false);
}

void UHookComponent::ShowHook()
{
		if (uParticleSystem && uArrowComponent) 
		{
				uParticleSystem->SetBeamSourcePoint(0, uArrowComponent->GetComponentLocation(), 0);
				uParticleSystem->SetBeamTargetPoint(0, m_hookLocation, 0);
		}
}

void UHookComponent::BeginPlay()
{
		Super::BeginPlay();

		/*Init pointers*/
		uParticleSystem = Character->PistolParticleSystem;
		uArrowComponent = Character->PistolMuzzleCompCpp;
		ResetGrappleHook();
}

void UHookComponent::ExecutePower()
{
		FVector A, B, InitForce(0, 0, 500);
		FTimerHandle TimerHandleInit, TimerHandleForce;

		if (Character->GetCameraShot(A, B))
		{
				m_hookLocation = B;
				ShootGrappleHook();
				LaunchCharacter(InitForce, true);

				GetWorld()->GetTimerManager().SetTimer(TimerHandleInit, this, &UHookComponent::LaunchCharacterForce, 0.2f, false);
				GetWorld()->GetTimerManager().SetTimer(TimerHandleForce, this, &UHookComponent::ResetGrappleHook, 0.5f, false);
		}
		else
				ResetGrappleHook();
}

void UHookComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
		Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

		if(uParticleSystem->IsVisible())
				ShowHook();
}