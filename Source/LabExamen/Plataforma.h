#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Plataforma.generated.h"

class UStaticMeshComponent;

UCLASS(Abstract)
class LABEXAMEN_API APlataforma : public AActor
{
	GENERATED_BODY()

public:
	APlataforma();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Plataforma")
	UStaticMeshComponent* MallaPlataforma;

public:
	virtual void Tick(float DeltaTime) override;

	// Metodo polimorfico para reaccionar al impacto de la pelota
	virtual void AlImpactarConPelota();
};