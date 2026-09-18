#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pelota.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;

UCLASS()
class LABEXAMEN_API APelota : public AActor
{
	GENERATED_BODY()

public:
	APelota();

	/* Componente de colision esferico */
	UPROPERTY(VisibleDefaultsOnly, Category = "Pelota")
	USphereComponent* ColisionEsfera;

	/* Malla visual */
	UPROPERTY(VisibleDefaultsOnly, Category = "Pelota")
	UStaticMeshComponent* MallaPelota;

	/* Movimiento con rebote automatico */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movimiento")
	UProjectileMovementComponent* MovimientoProyectil;

	/* Delegado de impacto */
	UFUNCTION()
	void AlImpactar(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	virtual void BeginPlay() override;
};