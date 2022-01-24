#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Subject15Character.generated.h"

UCLASS()
class SUBJECT16_API ASubject15Character : public ACharacter {
  GENERATED_BODY()

public:
  ASubject15Character();

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
  USpringArmComponent *SpringArm;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
  UCameraComponent *Camera;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
  UStaticMeshComponent *Pistol;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
  UArrowComponent *Arrow;

protected:
  virtual void BeginPlay() override;

public:
  virtual void Tick(float DeltaTime) override;

  virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;
};
