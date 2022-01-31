// Fill out your copyright notice in the Description page of Project Settings.


#include "HookComponent.h"

/*Init values*/
UHookComponent::UHookComponent() 
{
		m_maxDistance = 2500.f;
		m_canGrappleHook = true;
		m_hookLocation = FVector(0, 0, 0);
}

void UHookComponent::BeginPlay()
{
		Super::BeginPlay();
}

void UHookComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
		Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}