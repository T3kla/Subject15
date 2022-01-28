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

#include "Public/PowerBaseComponent.h"
#include "Subject15Character.generated.h"

// TODO: Hook to capsule component to get overlap events to look for power pickups
// TODO: Add every power to the thing

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
    UArrowComponent *ArrowCompCpp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    USceneComponent *PistolFXPointCompCpp; // Effects attatch to this

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    UMaterial *GunMaterialCpp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    UPowerBaseComponent* PowerBaseComponent;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
        UPowerBaseComponent* PowerBaseComponent2;


    // UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    // UPowerPushPullComponent *PowerPushPullCompCpp;

    // UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    // UPowerActivationComponent *PowerActivationCompCpp;

    // UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    // UPowerExplosionComponent *PowerExplosionCompCpp;

    // UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    // UPowerHookComponent *PowerHookCompCpp;

    // UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    // UPowerPhaseComponent *PowerPhaseCompCpp;

  private:
    UMaterialInstanceDynamic *GunDynMaterialCpp;

    EPowers SlotOnePower = EPowers::None;
    EPowers SlotTwoPower = EPowers::None;
    EPowers CurrentPower = EPowers::None;

    UPowerBaseComponent* CurrentPowerBase = nullptr;
    TArray<UPowerBaseComponent*> M_PowerList;
    //std::vector<UPowerBaseComponent*> M_PowerList;

  protected:
    virtual void BeginPlay() override;

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
    void OnPowerPressed();
    void OnPowerReleased();

    void ChangePower(EPowers NewPower, int IntPowerChoose);

  public:
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;
   
    UMaterialInstanceDynamic* GetGunDynMaterialCpp();
    
    void SetGunDynMaterialCpp(FColor& CurrentColorPower);
};
