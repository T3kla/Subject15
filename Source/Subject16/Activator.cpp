#include "Activator.h"

AActivator::AActivator()
{
    PrimaryActorTick.bCanEverTick = false;

    RootCompCpp = CreateDefaultSubobject<USceneComponent>(TEXT("RootCompCpp"));
    SetRootComponent(RootCompCpp);

    PanelEmissiveCompCpp =
        CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PanelEmissiveCompCpp"));
    PanelEmissiveCompCpp->SetupAttachment(RootCompCpp);
}

void AActivator::BeginPlay()
{
    Super::BeginPlay();

    // Create Dyn Material
    EmissiveDynMaterial = UMaterialInstanceDynamic::Create(EmissiveMaterial, this);

    // Assign Dyn Material
    auto Materials = PanelEmissiveCompCpp->GetMaterials();
    for (size_t i = 0; i < PanelEmissiveCompCpp->GetMaterials().Num(); i++)
        PanelEmissiveCompCpp->SetMaterial(i, EmissiveDynMaterial);

    // Set initial emissive
    if (EmissiveDynMaterial)
        EmissiveDynMaterial->SetScalarParameterValue("Emissive", EmissiveWhenNotActive);
}

void AActivator::Activate()
{
    IsActive = true;

    // Activate dependacies
    for (auto &&Activable : ActivablesArray)
        Activable->Activate();

    // Change emissive
    if (EmissiveDynMaterial)
        EmissiveDynMaterial->SetScalarParameterValue("Emissive", EmissiveWhenActive);
}

void AActivator::Deactivate()
{
    IsActive = false;

    // Deactivate dependacies
    for (auto &&Activable : ActivablesArray)
        Activable->Deactivate();

    // Change emissive
    if (EmissiveDynMaterial)
        EmissiveDynMaterial->SetScalarParameterValue("Emissive", EmissiveWhenNotActive);
}