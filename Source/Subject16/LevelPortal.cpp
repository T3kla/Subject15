#include "LevelPortal.h"
#include "LevelPortalStructureCpp.h"
#include "Containers/UnrealString.h"
#include "GameFramework/Character.h"

ALevelPortal::ALevelPortal()
{
    PrimaryActorTick.bCanEverTick = true;

    RootCompCpp = CreateDefaultSubobject<USceneComponent>(TEXT("RootCompCpp"));
    SetRootComponent(RootCompCpp);

    BoxCompCpp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCompCpp"));
    BoxCompCpp->SetupAttachment(RootCompCpp);

    PortalParticleSystemCompCpp =
        CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PortalParticleSystemCompCpp"));
    PortalParticleSystemCompCpp->SetupAttachment(RootCompCpp);
}

void ALevelPortal::BeginPlay()
{
    Super::BeginPlay();

    // Bind to Box Collision
    BoxCompCpp->OnComponentBeginOverlap.AddDynamic(this, &ALevelPortal::OnOverlap);

    // Get Player Cam
    if (AllowTravel && GEngine)
        PlayerCam = GEngine->GetFirstLocalPlayerController(GetWorld())->PlayerCameraManager;
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

    if (!LevelPortalDataTableCpp)
    {
        if (GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Red, "Portal: DataTable not set!");

        return;
    }

    if (TravelOverride.Compare({"None"}) != 0)
    {
        if (GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Red, "Lmao1");
        UGameplayStatics::OpenLevel(GetWorld(), TravelOverride);
        return;
    }
    else
    {
        if (GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Red, "Lmao2");
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
            if (GEngine)
                GEngine->AddOnScreenDebugMessage(
                    -1, 2.5f, FColor::Red, FString::Printf(TEXT("Portal: Traveling to %s"), *dest));

            // FIXME: if DestinationLevel isn't the exact name of a level, this crashes
            UGameplayStatics::OpenLevel(GetWorld(), pair->DestinationLevel);

            return;
        }
    }
}
