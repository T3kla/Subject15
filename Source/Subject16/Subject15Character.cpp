#include "Subject15Character.h"

ASubject15Character::ASubject15Character() {
  PrimaryActorTick.bCanEverTick = true;

  auto *Capsule = GetCapsuleComponent();
  SetRootComponent(Capsule);

  SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
  SpringArm->SetupAttachment(Capsule);

  Pistol = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PistolComp"));
  Pistol->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

  Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
  Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

  Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComp"));
  Arrow->SetupAttachment(Pistol);
}

void ASubject15Character::BeginPlay() { Super::BeginPlay(); }

void ASubject15Character::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

void ASubject15Character::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) {
  Super::SetupPlayerInputComponent(PlayerInputComponent);
}
