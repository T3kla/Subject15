#include "Subject15Character.h"

ASubject15Character::ASubject15Character() {
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

void ASubject15Character::BeginPlay() {
  Super::BeginPlay();
  InputComponent->BindAxis("Forward", this, &ASubject15Character::MoveVertical);
  InputComponent->BindAxis("Right", this, &ASubject15Character::MoveHorizontal);
  InputComponent->BindAxis("LookUp", this, &ASubject15Character::Pitch);
  InputComponent->BindAxis("Turn", this, &ASubject15Character::Yaw);
}

void ASubject15Character::MoveVertical(float Amount) {
  if (Controller && Amount)
    AddMovementInput(CameraCompCpp->GetForwardVector(), Amount);
}
void ASubject15Character::MoveHorizontal(float Amount) {
  if (Controller && Amount)
    AddMovementInput(CameraCompCpp->GetRightVector(), Amount);
}

void ASubject15Character::Pitch(float amount) {
  AddControllerPitchInput(200.f * amount * GetWorld()->GetDeltaSeconds());
}

void ASubject15Character::Yaw(float amount) {
  AddControllerYawInput(200.f * amount * GetWorld()->GetDeltaSeconds());
}

void ASubject15Character::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

void ASubject15Character::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) {
  Super::SetupPlayerInputComponent(PlayerInputComponent);
}
