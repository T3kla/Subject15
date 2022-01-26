// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PowerBaseComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
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
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FColor* PowerColor;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		AActor* PowerVFX;

	UFUNCTION()
		void PullTrigger();
	UFUNCTION()
		void ReleaseTrigger();

	UFUNCTION()
		void ActivatePower();
	UFUNCTION()
		void DeactivatePower();

protected:
	UFUNCTION()
		virtual void FirePower();
};
