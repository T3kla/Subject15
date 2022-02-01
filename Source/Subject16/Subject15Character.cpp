#include "Subject15Character.h"
#include "DrawDebugHelpers.h"
#include "PowerActivationComponent.h"

ASubject15Character::ASubject15Character()
{
    PrimaryActorTick.bCanEverTick = true;

    // Set Capsule as root
    auto *Capsule = GetCapsuleComponent();
    SetRootComponent(Capsule);

    // Main components and attachment order
    SpringArmCompCpp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmCompCpp"));
    SpringArmCompCpp->SetupAttachment(Capsule);
    SpringArmCompCpp->bUsePawnControlRotation = true;

    PistolCompCpp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PistolCompCpp"));
    PistolCompCpp->SetupAttachment(SpringArmCompCpp, USpringArmComponent::SocketName);

    CameraCompCpp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraCompCpp"));
    CameraCompCpp->SetupAttachment(SpringArmCompCpp, USpringArmComponent::SocketName);

    PistolMuzzleCompCpp = CreateDefaultSubobject<UArrowComponent>(TEXT("PistolMuzzleCompCpp"));
    PistolMuzzleCompCpp->SetupAttachment(PistolCompCpp);

    PistolFXPointCompCpp = CreateDefaultSubobject<USceneComponent>(TEXT("PistolFXPointCompCpp"));
    PistolFXPointCompCpp->SetupAttachment(PistolCompCpp);

    PistolParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
    PistolParticleSystem->SetupAttachment(RootComponent);

    // Powers
    // PowerPushPullCompCpp =
    // CreateDefaultSubobject<UPowerPushPullComponent>(TEXT("PowerPushPullCompCpp"));

    PowerActivationCompCpp =
        CreateDefaultSubobject<UPowerActivationComponent>(TEXT("PowerActivationCompCpp"));

    PowerExplosionCompCpp =
        CreateDefaultSubobject<UPowerExplosionComponent>(TEXT("PowerExplosionCompCpp"));

    PowerHookCompCpp = CreateDefaultSubobject<UHookComponent>(TEXT("PowerHookCompCpp"));

    // PowerPhaseCompCpp =
    // CreateDefaultSubobject<UPowerPhaseComponent>(TEXT("PowerPhaseCompCpp"));
}

void ASubject15Character::BeginPlay()
{
    Super::BeginPlay();

    // Input Bindings
    InputComponent->BindAxis("Forward", this, &ASubject15Character::MoveVertical);
    InputComponent->BindAxis("Right", this, &ASubject15Character::MoveHorizontal);
    InputComponent->BindAxis("LookUp", this, &ASubject15Character::Pitch);
    InputComponent->BindAxis("Turn", this, &ASubject15Character::Yaw);
    InputComponent->BindAction("Jump", IE_Pressed, this, &ASubject15Character::JumpStart);
    InputComponent->BindAction("Jump", IE_Released, this, &ASubject15Character::JumpStop);
    InputComponent->BindAction("WeaponToSlot1", IE_Pressed, this, &ASubject15Character::SlotOne);
    InputComponent->BindAction("WeaponToSlot2", IE_Pressed, this, &ASubject15Character::SlotTwo);
    InputComponent->BindAction("Fire", IE_Pressed, this, &ASubject15Character::FirePressed);
    InputComponent->BindAction("Fire", IE_Released, this, &ASubject15Character::FireReleased);

    if (!GunMaterialCpp)
        return;

    // Create Dyn Material
    PistolDynMaterial = UMaterialInstanceDynamic::Create(GunMaterialCpp, this);

    // Assign Dyn Material
    auto Materials = PistolCompCpp->GetMaterials();
    for (size_t i = 0; i < PistolCompCpp->GetMaterials().Num(); i++)
        if (i > 0) // Skip first because it's the gun's body
            PistolCompCpp->SetMaterial(i, PistolDynMaterial);

    // Camera Fade In at level start
    if (GEngine)
    {
        auto *Cam = GEngine->GetFirstLocalPlayerController(GetWorld())->PlayerCameraManager;
        Cam->StartCameraFade(1.0f, 0.0f, 1.5f, {0.0f, 0.0f, 0.0f, 0.0f}, false, false);
    }
}
void ASubject15Character::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

#pragma region MovementRegion

FVector CleanMovement(FVector Forward)
{
    auto Result = FVector(Forward.X, Forward.Y, 0.f);
    Result.Normalize();
    return Result;
}

void ASubject15Character::MoveVertical(float Amount)
{
    if (Controller && Amount)
        AddMovementInput(CleanMovement(CameraCompCpp->GetForwardVector()), Amount);
}

void ASubject15Character::MoveHorizontal(float Amount)
{
    if (Controller && Amount)
        AddMovementInput(CleanMovement(CameraCompCpp->GetRightVector()), Amount);
}

void ASubject15Character::Pitch(float Amount)
{
    AddControllerPitchInput(100.f * Amount * GetWorld()->GetDeltaSeconds());
}

void ASubject15Character::Yaw(float Amount)
{
    AddControllerYawInput(100.f * Amount * GetWorld()->GetDeltaSeconds());
}

void ASubject15Character::JumpStart()
{
    Jump();
}

void ASubject15Character::JumpStop()
{
    StopJumping();
}

#pragma endregion

#pragma region InputEventsRegion

void ASubject15Character::SlotOne()
{
    CurrentSlot = 1;
    ChangePower(SlotOnePower);
}

void ASubject15Character::SlotTwo()
{
    CurrentSlot = 2;
    ChangePower(SlotTwoPower);
}

void ASubject15Character::FirePressed()
{
    if (CurrentPower)
        CurrentPower->FirePressed();
}

void ASubject15Character::FireReleased()
{
    if (CurrentPower)
        CurrentPower->FireReleased();
}

#pragma endregion

void ASubject15Character::SetSlot(EPowers NewPower)
{
    if (CurrentSlot == 1)
        SlotOnePower = NewPower;
    else if (CurrentSlot == 2)
        SlotTwoPower = NewPower;

    ChangePower(NewPower);
}

void ASubject15Character::SetPistolColor(const FColor &CurrentColorPower)
{
    if (PistolDynMaterial)
        PistolDynMaterial->SetVectorParameterValue("Color", CurrentColorPower);
}

void ASubject15Character::ChangePower(EPowers NewPower)
{
    if (CurrentPowerEnum == NewPower)
        return;

    // Deactivate old Power
    if (CurrentPower)
        CurrentPower->DeactivatePower();

    // Select new Current
    switch (NewPower)
    {
    case EPowers::Activation:
        CurrentPower = PowerActivationCompCpp;
        break;
    case EPowers::Hook:
        CurrentPower = PowerHookCompCpp;
        break;
    case EPowers::Explosion:
        CurrentPower = PowerExplosionCompCpp;
        break;
    default:
        CurrentPower = nullptr;
        SetPistolColor({1, 1, 1, 1});
        break;
    }

    // Activate new Power
    if (CurrentPower)
        CurrentPower->ActivatePower();

    CurrentPowerEnum = NewPower;
}

bool ASubject15Character::GetCameraShot(FVector &Start, FVector &End, FHitResult &HitResult)
{
    FVector A = CameraCompCpp->GetComponentLocation();
    FVector B = A + CameraCompCpp->GetForwardVector() * 10000.f;

    FHitResult RV_Hit(ForceInit);
    FCollisionQueryParams RV_TraceParams =
        FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);

    RV_TraceParams.bTraceComplex = true;
    RV_TraceParams.bReturnPhysicalMaterial = true;

    auto Hit = GetWorld()->LineTraceSingleByChannel(RV_Hit, A, B, ECC_Pawn, RV_TraceParams);

    if (!Hit)
    {
        Start = A;
        End = B;
    }
    else
    {
        Start = A;
        End = RV_Hit.ImpactPoint;
        HitResult = RV_Hit;
    }

    DrawDebugLine(GetWorld(), Start, End, {255, 1, 1, 255}, false, 2.f, 0, 1.f);
    return Hit;
}

bool ASubject15Character::GetPistolShot(FVector &Start, FVector &End, FHitResult &HitResult)
{
    FVector A;
    auto Hit = GetCameraShot(A, End, HitResult);

    Start = PistolMuzzleCompCpp->GetComponentLocation();

    DrawDebugLine(GetWorld(), Start, End, {1, 255, 1, 1}, false, 2.f, 0, 1.f);
    return Hit;
}