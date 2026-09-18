#include "PlataformaDestructible.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInterface.h"

APlataformaDestructible::APlataformaDestructible()
{
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialOro(TEXT("/Game/StarterContent/Materials/M_Metal_Gold.M_Metal_Gold"));
	if (MaterialOro.Succeeded())
	{
		MallaPlataforma->SetMaterial(0, MaterialOro.Object);
	}
}

void APlataformaDestructible::AlImpactarConPelota()
{
	UE_LOG(LogTemp, Warning, TEXT("Plataforma Destructible impactada: destruyendose."));
	Destroy();
}