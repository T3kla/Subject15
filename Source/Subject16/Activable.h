#pragma once

#include "CoreMinimal.h"
#include "Activable.generated.h"

UCLASS()
class SUBJECT16_API AActivable : public AActor
{
    GENERATED_BODY()

  public:
    UFUNCTION(BlueprintCallable)
    void Activate();

    UFUNCTION(BlueprintCallable)
    void Deactivate();

  protected:
    AActivable();
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
};
