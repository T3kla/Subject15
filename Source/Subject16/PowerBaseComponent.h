#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnumFireMode.h"
#include "ProjectileBase.h"
#include "Engine/Texture.h"
#include "PowerBaseComponent.generated.h"

class ASubject15Character;

UCLASS()
class SUBJECT16_API UPowerBaseComponent : public UActorComponent
{
    GENERATED_BODY()

  public:
    UPowerBaseComponent();

    UFUNCTION()
    virtual void FirePressed();

    UFUNCTION()
    virtual void FireReleased();

    UFUNCTION()
    virtual void ActivatePower();

    UFUNCTION()
    virtual void DeactivatePower();

    UFUNCTION()
    virtual void ExecutePower();

    void PlayPowerSound();

  protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType,
                               FActorComponentTickFunction *ThisTickFunction) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EFireMode FireMode = EFireMode::None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FireRate = 1.f;

    UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
    TSubclassOf<AProjectileBase> ProjectilePowerType;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FColor PowerColor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USoundBase *PowerSoundFX;

    

    void SetCooldown(float Modifier = 0.f);
    void ResetCooldown();

    FTimerHandle AutomaticTimer;
    FTimerHandle CooldownTimer;
    bool IsInCooldown = false;

    ASubject15Character *Character;

public:
    /*Crear variable FText Name para el power y UTexture para Img HUD*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        UTexture* PowerImg;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FText PowerName;
};
