#include "Subject15Character.h"

ASubject15Character::ASubject15Character()
{
    PrimaryActorTick.bCanEverTick = true;

    auto *Capsule = GetCapsuleComponent();
    SetRootComponent(Capsule);

    SpringArmCompCpp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmCompCpp"));
    SpringArmCompCpp->SetupAttachment(Capsule);
    SpringArmCompCpp->bUsePawnControlRotation = true;

    PistolCompCpp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PistolCompCpp"));
    PistolCompCpp->SetupAttachment(SpringArmCompCpp, USpringArmComponent::SocketName);

    CameraCompCpp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraCompCpp"));
    CameraCompCpp->SetupAttachment(SpringArmCompCpp, USpringArmComponent::SocketName);

    ArrowCompCpp = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowCompCpp"));
    ArrowCompCpp->SetupAttachment(PistolCompCpp);
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

    if (!GunMaterialCpp)
        return;

    // Create Dyn Material
    GunDynMaterialCpp = UMaterialInstanceDynamic::Create(GunMaterialCpp, this);

    // Assign Dyn Material
    auto Materials = PistolCompCpp->GetMaterials();
    for (size_t i = 0; i < PistolCompCpp->GetMaterials().Num(); i++)
        if (i > 0) // Skip first
            PistolCompCpp->SetMaterial(i, GunDynMaterialCpp);
}

void ASubject15Character::MoveVertical(float Amount)
{
    if (Controller && Amount)
        AddMovementInput(CameraCompCpp->GetForwardVector(), Amount);
}
void ASubject15Character::MoveHorizontal(float Amount)
{
    if (Controller && Amount)
        AddMovementInput(CameraCompCpp->GetRightVector(), Amount);
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

void ASubject15Character::SlotOne()
{
    if (GunDynMaterialCpp)
        GunDynMaterialCpp->SetVectorParameterValue("Color", {1.f, 0.f, 0.f, 0.f});
}

void ASubject15Character::SlotTwo()
{
    if (GunDynMaterialCpp)
        GunDynMaterialCpp->SetVectorParameterValue("Color", {0.f, 1.f, 0.f, 0.f});
}

void ASubject15Character::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ASubject15Character::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}