// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerBaseComponent.h"
#include "PowerExplosionComponent.generated.h"


UCLASS()
class SUBJECT16_API UPowerExplosionComponent : public UPowerBaseComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPowerExplosionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;		
};
