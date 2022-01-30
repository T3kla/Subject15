#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "Altar.generated.h"

UCLASS()
class SUBJECT16_API AAltar : public AActor
{
    GENERATED_BODY()

  public:
    AAltar();

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    USceneComponent *RootCompCpp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    UCapsuleComponent *CapsuleCompCpp;

  protected:
    virtual void BeginPlay() override;

  private:
    APlayerCameraManager *PlayerCam;

  public:
    virtual void Tick(float DeltaTime) override;

  private:
    UFUNCTION()
    void OnOverlap(UPrimitiveComponent *OverlappedComp, AActor *Other,
                   UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                   const FHitResult &SweepResult);
};
