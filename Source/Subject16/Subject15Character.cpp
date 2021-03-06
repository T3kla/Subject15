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

    AudioComponentSystem = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioCompCpp"));
    AudioComponentSystem->SetupAttachment(RootComponent);

    GrabLocation = CreateDefaultSubobject<USceneComponent>(TEXT("GrabLocation"));
    GrabLocation->SetupAttachment(CameraCompCpp);

    PistolMuzzleCompCpp = CreateDefaultSubobject<UArrowComponent>(TEXT("PistolMuzzleCompCpp"));
    PistolMuzzleCompCpp->SetupAttachment(PistolCompCpp);

    PistolFXPointCompCpp = CreateDefaultSubobject<USceneComponent>(TEXT("PistolFXPointCompCpp"));
    PistolFXPointCompCpp->SetupAttachment(PistolCompCpp);

    PistolParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
    PistolParticleSystem->SetupAttachment(RootComponent);

    GrabbingParticleSystem =
        CreateDefaultSubobject<UParticleSystemComponent>(TEXT("GrabbingParticleSystem"));
    GrabbingParticleSystem->SetupAttachment(RootComponent);

    // Physics Handle for push/pull power
    PhysicsHandleCompCpp =
        CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandleCompCpp"));

    // Powers
    PowerPushPullCompCpp =
        CreateDefaultSubobject<UPowerPushPullComponent>(TEXT("PowerPushPullCompCpp"));

    PowerActivationCompCpp =
        CreateDefaultSubobject<UPowerActivationComponent>(TEXT("PowerActivationCompCpp"));

    PowerExplosionCompCpp =
        CreateDefaultSubobject<UPowerExplosionComponent>(TEXT("PowerExplosionCompCpp"));

    PowerHookCompCpp = CreateDefaultSubobject<UPowerHookComponent>(TEXT("PowerHookCompCpp"));

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
    InputComponent->BindAction("PullCube", IE_Pressed, this, &ASubject15Character::PullCube);
    InputComponent->BindAction("PushCube", IE_Pressed, this, &ASubject15Character::PushCube);

    // Clean Slots
    for (auto &&Power : Slots)
        Power = EPowers::None;

    // Camera Fade In at level start
    if (GEngine)
    {
        auto *Cam = GEngine->GetFirstLocalPlayerController(GetWorld())->PlayerCameraManager;
        Cam->StartCameraFade(1.0f, 0.0f, 1.5f, {0.0f, 0.0f, 0.0f, 0.0f}, false, false);
    }

    if (!GunMaterialCpp)
        return;

    // Create Dyn Material
    PistolDynMaterial = UMaterialInstanceDynamic::Create(GunMaterialCpp, this);

    // Assign Dyn Material
    auto Materials = PistolCompCpp->GetMaterials();
    for (size_t i = 0; i < PistolCompCpp->GetMaterials().Num(); i++)
        if (i > 0) // Skip first because it's the gun's body
            PistolCompCpp->SetMaterial(i, PistolDynMaterial);

    // Grabbed cube movement velocity
    PhysicsHandleCompCpp->InterpolationSpeed = 5.0f;

    // Set the initial grabbed cube location
    GrabLocation->SetRelativeLocation(GrabInitialLocation);
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
    ChangePower(Slots[0]);
}

void ASubject15Character::SlotTwo()
{
    CurrentSlot = 2;
    ChangePower(Slots[1]);
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

void ASubject15Character::PushCube()
{
    if (CurrentPowerEnum == EPowers::PushPull)
    {
        Cast<UPowerPushPullComponent>(CurrentPower)->PushObject();
    }
}

void ASubject15Character::PullCube()
{
    if (CurrentPowerEnum == EPowers::PushPull)
    {
        Cast<UPowerPushPullComponent>(CurrentPower)->PullObject();
    }
}

#pragma endregion

void ASubject15Character::SetSlot(EPowers NewPower)
{
    for (auto &i : Slots)
    {
        if (i == NewPower)
            return;

        else if (i == EPowers::None)
        {
            i = NewPower;
            ChangePower(i);
            return;
        }
    }

    switch (CurrentSlot)
    {
    case 1:
        Slots[0] = NewPower;
        break;

    case 2:
        Slots[1] = NewPower;
        break;
    }

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
    case EPowers::PushPull:
        CurrentPower = PowerPushPullCompCpp;
        break;
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
    {
        OnPowerChange(CurrentPower->PowerImg, CurrentPower->PowerName); //Cambiar PowerInfo en HUD BP Implement
        CurrentPower->ActivatePower();
    }

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

    // DrawDebugLine(GetWorld(), Start, End, {255, 1, 1, 255}, false, 2.f, 0, 1.f);
    return Hit;
}

bool ASubject15Character::GetPistolShot(FVector &Start, FVector &End, FHitResult &HitResult)
{
    FVector A;
    auto Hit = GetCameraShot(A, End, HitResult);

    Start = PistolMuzzleCompCpp->GetComponentLocation();

    // DrawDebugLine(GetWorld(), Start, End, {1, 255, 1, 1}, false, 2.f, 0, 1.f);
    return Hit;
}
