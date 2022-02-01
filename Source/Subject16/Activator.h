#pragma once

#include "CoreMinimal.h"
#include "Activable.h"
#include "Activator.generated.h"

UCLASS()
class SUBJECT16_API AActivator : public AActor
{
    GENERATED_BODY()

  public:
    UFUNCTION(BlueprintCallable)
    void Activate();

    UFUNCTION(BlueprintCallable)
    void Deactivate();

    UPROPERTY(EditInstanceOnly)
    TArray<AActivable *> ActivablesArray;

  protected:
    AActivator();
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
};
