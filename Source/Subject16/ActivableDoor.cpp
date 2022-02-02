#include "ActivableDoor.h"
#include "Engine/TargetPoint.h"
#include "Math/UnrealMathUtility.h"

AActivableDoor::AActivableDoor()
{
}

void AActivableDoor::BeginPlay()
{
    Super::BeginPlay();

    // Save positions
    if (InitialPosition && FinalPosition)
    {
        InitPos = InitialPosition->GetActorLocation();
        FinalPos = FinalPosition->GetActorLocation();
        if (GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Red, "Coge positions");
    }
    else
    {
        InitPos = GetActorLocation();
        FinalPos = GetActorLocation();
    }

    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Red,
                                         FString::Printf(TEXT("InitPos = %d"), InitPos.Z));
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Red,
                                         FString::Printf(TEXT("FinalPos = %d"), FinalPos.Z));
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

    // Update Position
    auto NewPosition = InitPos + (FinalPos - InitPos) * Progress;
    SetActorLocation(NewPosition);
}

void AActivableDoor::Activate()
{
    Super::Activate();
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Red, "Activate");
    IsActive = true;
}

void AActivableDoor::Deactivate()
{
    Super::Deactivate();
    GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Red, "DeActivate");

    IsActive = false;
}