#pragma once

#include "PowerBaseComponent.h"
#include "PowerPushPullComponent.h"
#include "PowerHookComponent.h"
#include "PowerActivationComponent.h"
#include "PowerExplosionComponent.h"

#include "CoreMinimal.h"
#include "PowersEnum.h"
#include "GameFramework/Character.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Materials/Material.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Engine/Texture.h"
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
    USceneComponent *GrabLocation;

    UPROPERTY()
    FVector GrabInitialLocation = FVector(250.0f, 0.0f, 20.0f);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    UStaticMeshComponent *PistolCompCpp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    UArrowComponent *PistolMuzzleCompCpp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    USceneComponent *PistolFXPointCompCpp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    UAudioComponent *AudioComponentSystem;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    UMaterial *GunMaterialCpp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    UParticleSystemComponent *PistolParticleSystem;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    UParticleSystemComponent *GrabbingParticleSystem;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    UPhysicsHandleComponent *PhysicsHandleCompCpp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    UPowerPushPullComponent *PowerPushPullCompCpp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    UPowerActivationComponent *PowerActivationCompCpp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    UPowerExplosionComponent *PowerExplosionCompCpp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    UPowerHookComponent *PowerHookCompCpp;

    UFUNCTION()
    void SetSlot(EPowers NewPower);

    UFUNCTION()
    void SetPistolColor(const FColor &CurrentColorPower);

    UFUNCTION()
    bool GetCameraShot(FVector &Start, FVector &End, FHitResult &HitResult);

    UFUNCTION()
    bool GetPistolShot(FVector &Start, FVector &End, FHitResult &HitResult);

    UFUNCTION(BlueprintImplementableEvent)
    void OnPowerChange(const UTexture *PowerImg, const FText &PowerName);

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
    void PushCube();
    void PullCube();

    void ChangePower(EPowers NewPower);

    // Dyn mat for gun color change
    UMaterialInstanceDynamic *PistolDynMaterial;

    // Power Change variables
    EPowers Slots[2];

    EPowers CurrentPowerEnum = EPowers::None;
    uint8 CurrentSlot = 1;
    TArray<UPowerBaseComponent *> PowerArray;

  public:
    UPowerBaseComponent *CurrentPower = nullptr;
};
