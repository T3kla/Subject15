#include "ActivableDoor.h"
#include "Engine/TargetPoint.h"
#include "Math/UnrealMathUtility.h"
#include "Curves/CurveFloat.h"

AActivableDoor::AActivableDoor()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AActivableDoor::BeginPlay()
{
    Super::BeginPlay();

    // Save positions
    if (TargetInitial && TargetFinal)
    {
        InitPos = TargetInitial->GetActorLocation();
        FinalPos = TargetFinal->GetActorLocation();
    }
    else
    {
        InitPos = GetActorLocation();
        FinalPos = GetActorLocation();
    }
}

void AActivableDoor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Update Progress
    if (IsActive)
        Progress += Speed / 1000.f;
    else
        Progress -= Speed / 1000.f;

    // Clamp Progress
    Progress = Progress > 1.f ? 1.f : Progress < 0.f ? 0.f : Progress;
    auto AnimProg = AnimationCurve->GetFloatValue(Progress);

    // Update Position
    auto NewPosition = InitPos + (FinalPos - InitPos) * AnimProg;
    SetActorLocation(NewPosition);
}

void AActivableDoor::Activate()
{
    Super::Activate();

    IsActive = true;
}

void AActivableDoor::Deactivate()
{
    Super::Deactivate();

    IsActive = false;
}