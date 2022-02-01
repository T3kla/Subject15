// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ArrowComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "CoreMinimal.h"
#include "PowerBaseComponent.h"
#include "HookComponent.generated.h"

UCLASS()
class SUBJECT16_API UHookComponent : public UPowerBaseComponent
{
	GENERATED_BODY()

	/*Constructor*/
public:
	UHookComponent();

	UFUNCTION()
			void ShootGrappleHook();

	UFUNCTION()
			void ResetGrappleHook();

	UFUNCTION()
			void LaunchCharacter(FVector& Velocity, bool Override);

	UFUNCTION()
			void LaunchCharacterForce();

	UFUNCTION()
			void ShowHook();

protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

public:
		virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		virtual void ExecutePower() override;
		virtual void ActivatePower() override;

		UPROPERTY()
				UParticleSystemComponent* uParticleSystem;

		UPROPERTY()
				UArrowComponent* uArrowComponent;

private:
		bool m_canGrappleHook;
		FVector m_hookLocation;
	
};
