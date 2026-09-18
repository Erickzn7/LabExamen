#include "EscenarioJuego.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "PlataformaDestructible.h"
#include "PlataformaIndestructible.h"

AEscenarioJuego::AEscenarioJuego()
{
	PrimaryActorTick.bCanEverTick = false;

	EscenaRaiz = CreateDefaultSubobject<USceneComponent>(TEXT("EscenaRaizEscenario"));
	RootComponent = EscenaRaiz;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CuboFinder(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	UStaticMesh* MallaCubo = CuboFinder.Succeeded() ? CuboFinder.Object : nullptr;

	// 1. Muro Izquierdo
	MuroIzquierdo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CompMuroIzquierdo"));
	MuroIzquierdo->SetupAttachment(RootComponent);
	if (MallaCubo)
	{
		MuroIzquierdo->SetStaticMesh(MallaCubo);
	}
	MuroIzquierdo->SetRelativeLocation(FVector(600.0f, -800.0f, 0.0f));
	MuroIzquierdo->SetWorldScale3D(FVector(16.0f, 0.5f, 1.0f));
	MuroIzquierdo->SetCollisionProfileName(TEXT("BlockAll"));

	// 2. Muro Derecho
	MuroDerecho = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CompMuroDerecho"));
	MuroDerecho->SetupAttachment(RootComponent);
	if (MallaCubo)
	{
		MuroDerecho->SetStaticMesh(MallaCubo);
	}
	MuroDerecho->SetRelativeLocation(FVector(600.0f, 800.0f, 0.0f));
	MuroDerecho->SetWorldScale3D(FVector(16.0f, 0.5f, 1.0f));
	MuroDerecho->SetCollisionProfileName(TEXT("BlockAll"));

	// 3. Muro Superior
	MuroSuperior = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CompMuroSuperior"));
	MuroSuperior->SetupAttachment(RootComponent);
	if (MallaCubo)
	{
		MuroSuperior->SetStaticMesh(MallaCubo);
	}
	MuroSuperior->SetRelativeLocation(FVector(1400.0f, 0.0f, 0.0f));
	MuroSuperior->SetWorldScale3D(FVector(0.5f, 16.5f, 1.0f));
	MuroSuperior->SetCollisionProfileName(TEXT("BlockAll"));

	// 4. Muro Inferior
	MuroInferior = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CompMuroInferior"));
	MuroInferior->SetupAttachment(RootComponent);
	if (MallaCubo)
	{
		MuroInferior->SetStaticMesh(MallaCubo);
	}
	MuroInferior->SetRelativeLocation(FVector(-200.0f, 0.0f, 0.0f));
	MuroInferior->SetWorldScale3D(FVector(0.5f, 16.5f, 1.0f));
	MuroInferior->SetCollisionProfileName(TEXT("BlockAll"));
}

void AEscenarioJuego::BeginPlay()
{
	Super::BeginPlay();

	GenerarPlataformasAleatorias();
}

void AEscenarioJuego::GenerarPlataformasAleatorias()
{
	UWorld* const World = GetWorld();
	if (!World) return;

	const int32 CantidadPlataformas = FMath::RandRange(5, 20);

	const int32 FilasMax = 5;
	const int32 ColumnasMax = 6;
	const float SeparacionX = 140.0f;
	const float SeparacionY = 220.0f;
	const FVector PuntoInicio = GetActorLocation() + FVector(500.0f, -550.0f, 0.0f);

	TArray<FVector> PosicionesDisponibles;
	for (int32 Fila = 0; Fila < FilasMax; ++Fila)
	{
		for (int32 Col = 0; Col < ColumnasMax; ++Col)
		{
			PosicionesDisponibles.Add(PuntoInicio + FVector(Fila * SeparacionX, Col * SeparacionY, 0.0f));
		}
	}

	for (int32 i = PosicionesDisponibles.Num() - 1; i > 0; --i)
	{
		int32 IndiceAleatorio = FMath::RandRange(0, i);
		PosicionesDisponibles.Swap(i, IndiceAleatorio);
	}

	for (int32 i = 0; i < CantidadPlataformas; ++i)
	{
		const FVector Posicion = PosicionesDisponibles[i];
		const FRotator Rotacion = FRotator::ZeroRotator;

		FActorSpawnParameters ParametrosSpawn;
		ParametrosSpawn.Owner = this;

		const bool bEsDestructible = FMath::FRand() < 0.7f;
		if (bEsDestructible)
		{
			World->SpawnActor<APlataformaDestructible>(APlataformaDestructible::StaticClass(), Posicion, Rotacion, ParametrosSpawn);
		}
		else
		{
			World->SpawnActor<APlataformaIndestructible>(APlataformaIndestructible::StaticClass(), Posicion, Rotacion, ParametrosSpawn);
		}
	}
}