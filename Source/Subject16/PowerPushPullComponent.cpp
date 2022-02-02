#include "PowerPushPullComponent.h"
#include "Subject15Character.h"

UPowerPushPullComponent::UPowerPushPullComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	IsHolding = false;
}

void UPowerPushPullComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPowerPushPullComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Character->PhysicsHandleCompCpp->SetTargetLocation(Character->GrabLocation->GetComponentTransform().GetLocation());
	if (IsValid(PhysicsObject))
	{
		if (PhysicsObject->GetComponentVelocity().Size() <= 0.0f && !IsHolding)
		{
			PhysicsObject->SetMobility(EComponentMobility::Static);
			PhysicsObject->SetSimulatePhysics(false);
		}
	}
}

void UPowerPushPullComponent::FirePressed()
{
	Super::FirePressed();
}

void UPowerPushPullComponent::FireReleased()
{
	Super::FireReleased();
}

void UPowerPushPullComponent::ActivatePower()
{
	Super::ActivatePower();
}

void UPowerPushPullComponent::DeactivatePower()
{
	Super::DeactivatePower();
}

void UPowerPushPullComponent::ExecutePower()
{
	Super::ExecutePower();

	if (!IsHolding)
	{
		Grab();
	}
	else
	{
		Drop();
	}
}

void UPowerPushPullComponent::Grab()
{
	FVector A, B;
	FHitResult HitResult(ForceInit);

	if (Character->GetPistolShot(A, B, HitResult))
	{
		if (HitResult.Component->ComponentHasTag("GrabCube") && B.Distance(A, B) <= 750.0f)
		{
			Character->GrabLocation->SetRelativeLocation(Character->GrabInitialLocation);
			PhysicsObject = Cast<UPrimitiveComponent>(HitResult.Component);
			PhysicsObject->SetMobility(EComponentMobility::Movable);
			PhysicsObject->SetSimulatePhysics(true);
			Character->PhysicsHandleCompCpp->GrabComponentAtLocation(Cast<UPrimitiveComponent>(HitResult.Component), "None", HitResult.Location);
			IsHolding = true;
			PhysicsObject->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
			PhysicsObject->SetAngularDamping(10.0f);
			PhysicsObject->SetAllPhysicsLinearVelocity(FVector(0.0f, 0.0f, 0.0f));
		}
	}
}

void UPowerPushPullComponent::Drop()
{
	if (IsValid(PhysicsObject))
	{
		Character->PhysicsHandleCompCpp->ReleaseComponent();
		IsHolding = false;
		PhysicsObject->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UPowerPushPullComponent::SetDampingDelay, 0.2f, false);		
	}
}

void UPowerPushPullComponent::PullObject()
{
	if (IsHolding)
	{
		if (Character->GrabLocation->GetRelativeLocation().X > Character->GrabInitialLocation.X)
		{
			Character->GrabLocation->AddRelativeLocation(FVector(-50.0f, 0.0f, 0.0f));
		}
	}
}

void UPowerPushPullComponent::PushObject()
{
	if (IsHolding)
	{
		if (Character->GrabLocation->GetRelativeLocation().X < 750.0f)
		{
			Character->GrabLocation->AddRelativeLocation(FVector(50.0f, 0.0f, 0.0f));
		}
	}
}

void UPowerPushPullComponent::SetDampingDelay()
{
	PhysicsObject->SetAngularDamping(10.0f);
}