#pragma once

#include "CoreMinimal.h"
#include "PowerBaseComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/ArrowComponent.h"
#include "PowerPushPullComponent.generated.h"

/**
 * 
 */
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
	void Grab();
	void Drop();

	void PullObject();
	void PushObject();

	void SetDampingDelay();

	void ShowLaser();

	bool IsHolding;

	UPROPERTY()
		UPrimitiveComponent* PhysicsObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystem* GrabTemplateParticle;

	FTimerHandle GrabTimerHandle;

private:
	UParticleSystemComponent* GrabParticleSystem;
	UArrowComponent* GrabPistolMuzzle;
};
