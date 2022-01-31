#include "Altar.h"

AAltar::AAltar()
{
    PrimaryActorTick.bCanEverTick = true;

    RootCompCpp = CreateDefaultSubobject<USceneComponent>(TEXT("RootCompCpp"));
    SetRootComponent(RootCompCpp);

    CapsuleCompCpp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCompCpp"));
    CapsuleCompCpp->SetupAttachment(RootCompCpp);
}

void AAltar::BeginPlay()
{
    Super::BeginPlay();

    // Bind to Capsule Collision
    CapsuleCompCpp->OnComponentBeginOverlap.AddDynamic(this, &AAltar::OnOverlap);
}

void AAltar::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AAltar::OnOverlap(UPrimitiveComponent *OverlappedComp, AActor *Other,
                       UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                       const FHitResult &SweepResult)
{

    if (Other->ActorHasTag("Player") && GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Blue, "Altar Overlap");
}
