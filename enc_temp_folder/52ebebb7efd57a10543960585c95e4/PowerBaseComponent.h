// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../EnumFireMode.h"

#include "../ProjectileClass.h"
#include "PowerBaseComponent.generated.h"


UCLASS()
class SUBJECT16_API UPowerBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPowerBaseComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	UFUNCTION()
		void PullTrigger();
	UFUNCTION()
		void ReleaseTrigger();

	UFUNCTION()
		void ActivatePower();
	UFUNCTION()
		virtual void DeactivatePower();

	UFUNCTION()
		void OnPowerChange();
private:
	//ASubject15Character* M_Owner = nullptr;



	FTimerHandle* FireTimerHandle = new FTimerHandle();

	FTransform FirePointTransform;
	FRotator CameraPitchRotator;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EFireMode FireMode = EFireMode::None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float FireRate = 0.3f;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AProjectileClass> ProjectilePowerType; //Projectil que se Spawnea dependiendo del poder

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FColor PowerColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* PowerVFX;

	UFUNCTION()
		virtual void FirePower();

};


