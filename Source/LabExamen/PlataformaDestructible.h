#pragma once

#include "CoreMinimal.h"
#include "Plataforma.h"
#include "PlataformaDestructible.generated.h"

UCLASS()
class LABEXAMEN_API APlataformaDestructible : public APlataforma
{
	GENERATED_BODY()

public:
	APlataformaDestructible();

	virtual void AlImpactarConPelota() override;
};