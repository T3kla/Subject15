#pragma once

#include "CoreMinimal.h"
#include "PowerBaseComponent.h"
#include "PowerPushPullComponent.generated.h"

UCLASS()
class SUBJECT16_API UPowerPushPullComponent : public UPowerBaseComponent
{
	GENERATED_BODY()
	
public:
	UPowerPushPullComponent();

	virtual void FirePressed() override;
	virtual void FireReleased() override;
	virtual void ActivatePower() override;
	virtual void DeactivatePower() override;
	virtual void ExecutePower() override;

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION()
		void Grab();

	UFUNCTION()
		void Drop();

	UFUNCTION()
		void PullObject();

	UFUNCTION()
		void PushObject();

	UFUNCTION()
		void SetDampingDelay();

	UPROPERTY()
		bool IsHolding;

	UPROPERTY()
		UPrimitiveComponent *PhysicsObject;

	FTimerHandle TimerHandle;
};
