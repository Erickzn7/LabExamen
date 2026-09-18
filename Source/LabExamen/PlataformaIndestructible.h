#pragma once

#include "CoreMinimal.h"
#include "Plataforma.h"
#include "PlataformaIndestructible.generated.h"

UCLASS()
class LABEXAMEN_API APlataformaIndestructible : public APlataforma
{
	GENERATED_BODY()

public:
	APlataformaIndestructible();

	virtual void AlImpactarConPelota() override;
};