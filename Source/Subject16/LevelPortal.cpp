#include "LevelPortal.h"
#include "LevelPortalStructureCpp.h"
#include "Containers/UnrealString.h"

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
}

void ALevelPortal::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
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

    UWorld *TheWorld = GetWorld();
    FString CurrentLevel = TheWorld->GetMapName();

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

            UGameplayStatics::OpenLevel(GetWorld(), pair->DestinationLevel);

            break;
        }
    }
}
