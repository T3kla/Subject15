#pragma once

#include "CoreMinimal.h"
#include "Activable.h"
#include "Activator.generated.h"

UCLASS()
class SUBJECT16_API AActivator : public AActor
{
    GENERATED_BODY()

  public:
    AActivator();
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    USceneComponent *RootCompCpp;

    UFUNCTION(BlueprintCallable)
    void Activate();

    UFUNCTION(BlueprintCallable)
    void Deactivate();

    UPROPERTY(VisibleInstanceOnly)
    bool IsActive;

  protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    UStaticMeshComponent *PanelEmissiveCompCpp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    UMaterial *EmissiveMaterial;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float EmissiveWhenActive = 24.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float EmissiveWhenNotActive = 0.f;

    UPROPERTY(EditInstanceOnly)
    TArray<AActivable *> ActivablesArray;

  private:
    UMaterialInstanceDynamic *EmissiveDynMaterial;

    bool Empty = false;
};
