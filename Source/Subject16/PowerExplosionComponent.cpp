// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerExplosionComponent.h"

// Sets default values for this component's properties
UPowerExplosionComponent::UPowerExplosionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UPowerExplosionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPowerExplosionComponent::FirePressed()
{
	Super::FirePressed();
}

void UPowerExplosionComponent::FireReleased()
{
	Super::FireReleased();
}

void UPowerExplosionComponent::ActivatePower()
{
	Super::ActivatePower();
}

void UPowerExplosionComponent::DeactivatePower()
{
	Super::DeactivatePower();
}

void UPowerExplosionComponent::ExecutePower()
{
	Super::ExecutePower();
}