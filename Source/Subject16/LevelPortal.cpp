#include "LevelPortal.h"
#include "LevelPortalStructureCpp.h"
#include "GameFramework/Character.h"

#include "GameFramework/Actor.h"
#include "Materials/MaterialInstance.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/DataTable.h"
#include "Components/BoxComponent.h"

ALevelPortal::ALevelPortal()
{
    PrimaryActorTick.bCanEverTick = true;

    RootCompCpp = CreateDefaultSubobject<USceneComponent>(TEXT("RootCompCpp"));
    SetRootComponent(RootCompCpp);

    BoxCompCpp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCompCpp"));
    BoxCompCpp->SetupAttachment(RootCompCpp, RootCompCpp->GetAttachSocketName());

    PortalParticleSystemCompCpp =
        CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PortalParticleSystemCompCpp"));
    PortalParticleSystemCompCpp->SetupAttachment(RootCompCpp, RootCompCpp->GetAttachSocketName());
}

void ALevelPortal::BeginPlay()
{
    Super::BeginPlay();

    // Bind to Box Collision
    BoxCompCpp->OnComponentBeginOverlap.AddDynamic(this, &ALevelPortal::OnOverlap);

    // Get Player Cam
    auto *Char = GEngine->GetFirstLocalPlayerController(GetWorld());
    if (AllowTravel && GEngine)
    {
        PlayerCam = Char->PlayerCameraManager;
    }
    else
    {
        auto CharPawn = Char->GetPawn();
        CharPawn->SetActorLocation(GetActorLocation() + GetActorForwardVector() * 100.f);
        Char->SetControlRotation(GetActorRotation());
    }
}

void ALevelPortal::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Fade with distance
    if (AllowTravel && PlayerCam)
    {
        auto PlayerCamPos = PlayerCam->GetCameraLocation();
        auto PortalPos = GetActorLocation();

        auto DistanceToPortal = FVector::Dist(PlayerCamPos, PortalPos);

        if (DistanceToPortal < StartFadeDistance)
        {
            auto Value = (StartFadeDistance - DistanceToPortal) / StartFadeDistance * FadeIntensity;
            Value = Value > 1.f ? 1.f : Value < 0.f ? 0.f : Value;

            PlayerCam->SetManualCameraFade(Value, {0.f, 0.f, 0.f, 0.f}, false);
        }
    }
}

void ALevelPortal::OnOverlap(UPrimitiveComponent *OverlappedComp, AActor *Other,
                             UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                             const FHitResult &SweepResult)
{
    if (!AllowTravel)
    {
        if (GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Yellow,
                                             "Portal: Allow Travel is false!");

        return;
    }

    if (!Other->ActorHasTag(TEXT("Player")))
    {
        if (GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Yellow,
                                             "Portal: Actor wasn't player!");

        return;
    }

    if (!LevelPortalDataTableCpp)
    {
        if (GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Red, "Portal: DataTable not set!");

        return;
    }

    if (TravelOverride.Compare({"None"}) != 0)
    {
        UGameplayStatics::OpenLevel(GetWorld(), TravelOverride);
        return;
    }

    FString CurrentLevel = GetWorld()->GetMapName();

    TArray<FName> RowNames;
    RowNames = LevelPortalDataTableCpp->GetRowNames();

    for (auto &&name : RowNames)
    {
        auto *pair = LevelPortalDataTableCpp->FindRow<FLevelPortalStructureCpp>(name, CurrentLevel);

        if (!pair || pair->OriginLevel == FName("None") || pair->DestinationLevel == FName("None"))
            continue;

        auto orig = pair->OriginLevel.ToString();
        auto dest = pair->DestinationLevel.ToString();

        if (CurrentLevel.Contains(orig))
        {
            // FIXME: if DestinationLevel isn't the exact name of a level, this crashes
            UGameplayStatics::OpenLevel(GetWorld(), pair->DestinationLevel);
            return;
        }
    }
}
