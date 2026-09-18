#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EscenarioJuego.generated.h"

class UStaticMeshComponent;

UCLASS()
class LABEXAMEN_API AEscenarioJuego : public AActor
{
	GENERATED_BODY()

public:
	AEscenarioJuego();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Escenario")
	USceneComponent* EscenaRaiz;

	/* Muros perimetrales */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Escenario")
	UStaticMeshComponent* MuroIzquierdo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Escenario")
	UStaticMeshComponent* MuroDerecho;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Escenario")
	UStaticMeshComponent* MuroSuperior;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Escenario")
	UStaticMeshComponent* MuroInferior;

	/* Generación de plataformas al iniciar */
	void GenerarPlataformasAleatorias();
};