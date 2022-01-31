// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ArrowComponent.h"
#include "Particles/ParticleSystem.h"
#include "CoreMinimal.h"
#include "PowerBaseComponent.h"
#include "HookComponent.generated.h"

UCLASS()
class SUBJECT16_API UHookComponent : public UPowerBaseComponent
{
	GENERATED_BODY()

	/*Constructor*/
	UHookComponent();

private:
		float m_maxDistance;
		bool m_canGrappleHook;
		FVector m_hookLocation;

protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

public:
		virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		UPROPERTY()
				UParticleSystem* uParticleSystem;

		UPROPERTY()
				UArrowComponent* uArrowComponent;
	
};
