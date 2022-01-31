#include "Subject15Character.h"

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

    ArrowCompCpp = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowCompCpp"));
    ArrowCompCpp->SetupAttachment(PistolCompCpp);

    PistolFXPointCompCpp = CreateDefaultSubobject<USceneComponent>(TEXT("PistolFXPointCompCpp"));
    PistolFXPointCompCpp->SetupAttachment(PistolCompCpp);

    PowerBaseComponent0 = CreateDefaultSubobject<UPowerBaseComponent>(TEXT("PowerBase0CompCpp"));
    PowerBaseComponent1 = CreateDefaultSubobject<UPowerBaseComponent>(TEXT("PowerBase1CompCpp"));

    M_PowerList.Init(nullptr, 2);
    // PowerPushPullCompCpp =
    // CreateDefaultSubobject<UPowerPushPullComponent>(TEXT("PowerPushPullCompCpp"));

    // PowerActivationCompCpp =
    // CreateDefaultSubobject<UPowerActivationComponent>(TEXT("PowerActivationCompCpp"));

    // PowerExplosionCompCpp =
    // CreateDefaultSubobject<UPowerExplosionComponent>(TEXT("PowerExplosionCompCpp"));

    // PowerHookCompCpp =
    // CreateDefaultSubobject<UPowerHookComponent>(TEXT("PowerHookCompCpp"));

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
    InputComponent->BindAction("Shoot", IE_Pressed, this, &ASubject15Character::OnPowerPressed);
    InputComponent->BindAction("Shoot", IE_Released, this, &ASubject15Character::OnPowerReleased);

    if (!GunMaterialCpp)
        return;

    // Create Dyn Material
    GunDynMaterialCpp = UMaterialInstanceDynamic::Create(GunMaterialCpp, this);

    // Assign Dyn Material
    auto Materials = PistolCompCpp->GetMaterials();
    for (size_t i = 0; i < PistolCompCpp->GetMaterials().Num(); i++)
    {
        if (i > 0) // Skip first because it's the gun's body
        {
            PistolCompCpp->SetMaterial(i, GunDynMaterialCpp);
        }
    }

    if (GEngine)
    {
        auto *Cam = GEngine->GetFirstLocalPlayerController(GetWorld())->PlayerCameraManager;
        Cam->StartCameraFade(1.0f, 0.0f, 1.5f, {0.0f, 0.0f, 0.0f, 0.0f}, false, false);
    }

    // Setup M_PowerList
    M_PowerList[0] = PowerBaseComponent0;
    M_PowerList[1] = PowerBaseComponent1;

    // Set up CurrentPower
    // CurrentPowerBase = PowerBaseComponent0; //Es redundante, se realiza abajo. Por claridad
    // dejarlo (?) "Init" de Poder al cambiarlo al primero
    ChangePower(SlotOnePower, 0); // Aqui ya estamos seteando el CurrentPowerBase
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

void ASubject15Character::Pitch(float amount)
{
    AddControllerPitchInput(200.f * amount * GetWorld()->GetDeltaSeconds());
}

void ASubject15Character::Yaw(float amount)
{
    AddControllerYawInput(200.f * amount * GetWorld()->GetDeltaSeconds());
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
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Blue, "SlotOne");

    // if (GunDynMaterialCpp)
    //	GunDynMaterialCpp->SetVectorParameterValue("Color", { 1.f, 0.f, 0.f, 0.f });
    /*CurrentPowerBase->DeactivatePower();*/
    /*CurrentPowerBase = (M_PowerList[0]);*/
    ChangePower(SlotOnePower, 0);
}

void ASubject15Character::SlotTwo()
{
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Blue, "SlotTwo");

    /*if (GunDynMaterialCpp)
        GunDynMaterialCpp->SetVectorParameterValue("Color", { 0.f, 1.f, 0.f, 0.f });*/

    ChangePower(SlotTwoPower, 1);
}

void ASubject15Character::OnPowerPressed()
{
    // Call pressed on CurrentPower component
    CurrentPowerBase->PullTrigger();
}

void ASubject15Character::OnPowerReleased()
{
    // Call released on CurrentPower component
    CurrentPowerBase->ReleaseTrigger();
}
#pragma endregion

void ASubject15Character::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ASubject15Character::SetGunDynMaterialCpp(
    FColor &CurrentColorPower) // TODO (Calde): Coger puntero/Ref al GunDynMatCpp en PowerBase y
                               // cambiarle el color desde alli
{
    if (GunDynMaterialCpp)
        GunDynMaterialCpp->SetVectorParameterValue("Color", CurrentColorPower);
}
UMaterialInstanceDynamic *ASubject15Character::GetGunDynMaterialCpp()
{
    return GunDynMaterialCpp;
}

void ASubject15Character::ChangePower(
    EPowers NewPower, int IntPowerChoose) // MAYBE: Bind event a Inputs WeaponToSlot1 y pasarle los
                                          // parametros (Ahorra metodos intermedios)
{
    // Call release (Desactivate) on CurrentPower component
    if (CurrentPowerBase)
    {
        CurrentPowerBase->DeactivatePower();
    }

    // Change the CurrentPower
    CurrentPowerBase = (M_PowerList[IntPowerChoose]);

    // Call OnPowerChange of CurrentPower
    CurrentPowerBase->OnPowerChange();
}
