#include "PlataformaIndestructible.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInterface.h"

APlataformaIndestructible::APlataformaIndestructible()
{
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialMetal(TEXT("/Game/StarterContent/Materials/M_Metal_Steel.M_Metal_Steel"));
	if (MaterialMetal.Succeeded())
	{
		MallaPlataforma->SetMaterial(0, MaterialMetal.Object);
	}
}

void APlataformaIndestructible::AlImpactarConPelota()
{
	UE_LOG(LogTemp, Log, TEXT("Plataforma Indestructible impactada: no sufre cambios."));
}