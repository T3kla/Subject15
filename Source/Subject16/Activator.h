#pragma once

#include "CoreMinimal.h"
#include "Activable.h"
#include "Activator.generated.h"

UCLASS()
class SUBJECT16_API AActivator : public AActor
{
    GENERATED_BODY()

  public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    USceneComponent *RootCompCpp;

    UFUNCTION(BlueprintCallable)
    void Activate();

    UFUNCTION(BlueprintCallable)
    void Deactivate();

    UPROPERTY(VisibleInstanceOnly)
    bool IsActive;

  protected:
    AActivator();
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FColor ColorIfActive = {255, 255, 255};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FColor ColorIfNotActive = {1, 1, 1};

    UPROPERTY(EditInstanceOnly)
    TArray<AActivable *> ActivablesArray;
};
