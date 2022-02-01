#pragma once

#include "CoreMinimal.h"
#include "PowersEnum.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Materials/Material.h"
#include "PowerBaseComponent.h"
#include "PowerActivationComponent.h"
#include "PowerExplosionComponent.h"
#include "Subject15Character.generated.h"

UCLASS()
class SUBJECT16_API ASubject15Character : public ACharacter
{
    GENERATED_BODY()

  public:
    ASubject15Character();

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    USpringArmComponent *SpringArmCompCpp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    UCameraComponent *CameraCompCpp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    UStaticMeshComponent *PistolCompCpp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    UArrowComponent *PistolMuzzleCompCpp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    USceneComponent *PistolFXPointCompCpp; // Effects attatch to this

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    UMaterial *GunMaterialCpp;

    // UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    // UPowerPushPullComponent *PowerPushPullCompCpp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    UPowerActivationComponent *PowerActivationCompCpp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    UPowerExplosionComponent *PowerExplosionCompCpp;

    // UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    // UPowerHookComponent *PowerHookCompCpp;

    // UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    // UPowerPhaseComponent *PowerPhaseCompCpp;

    UFUNCTION()
    void SetSlot(EPowers NewPower);

    UFUNCTION()
    void SetPistolColor(const FColor &CurrentColorPower);

    UFUNCTION()
    void GetCameraShot(FVector &Start, FVector &End);

    UFUNCTION()
    void GetPistolShot(FVector &Start, FVector &End);

  protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

  private:
    // Axes
    void MoveVertical(float Amount);
    void MoveHorizontal(float Amount);
    void Pitch(float Amount);
    void Yaw(float Amount);

    // Actions
    void JumpStart();
    void JumpStop();
    void SlotOne();
    void SlotTwo();
    void FirePressed();
    void FireReleased();

    void ChangePower(EPowers NewPower);

    // Dyn mat for gun color change
    UMaterialInstanceDynamic *PistolDynMaterial;

    // Power Change variables
    EPowers SlotOnePower = EPowers::None;
    EPowers SlotTwoPower = EPowers::None;
    EPowers CurrentPowerEnum = EPowers::None;
    uint8 CurrentSlot = 1;
    UPowerBaseComponent *CurrentPower = nullptr;
    TArray<UPowerBaseComponent *> PowerArray;
};
