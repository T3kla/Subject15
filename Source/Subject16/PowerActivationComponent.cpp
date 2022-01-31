#include "PowerActivationComponent.h"
#include "Subject15Character.h"

UPowerActivationComponent::UPowerActivationComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UPowerActivationComponent::BeginPlay()
{
    Super::BeginPlay();
}