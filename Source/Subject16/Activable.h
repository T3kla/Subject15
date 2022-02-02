#pragma once

#include "CoreMinimal.h"
#include "Activable.generated.h"

UCLASS()
class SUBJECT16_API AActivable : public AActor
{
    GENERATED_BODY()

  public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    USceneComponent *RootCompCpp;

    UFUNCTION(BlueprintCallable)
    virtual void Activate();

    UFUNCTION(BlueprintCallable)
    virtual void Deactivate();

  protected:
    AActivable();
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
};
