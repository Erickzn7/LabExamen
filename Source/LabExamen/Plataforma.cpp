#include "Plataforma.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

APlataforma::APlataforma()
{
	PrimaryActorTick.bCanEverTick = true;

	MallaPlataforma = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaPlataforma"));
	RootComponent = MallaPlataforma;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CuboMesh(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	if (CuboMesh.Succeeded())
	{
		MallaPlataforma->SetStaticMesh(CuboMesh.Object);
	}

	MallaPlataforma->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	MallaPlataforma->SetNotifyRigidBodyCollision(true);

	MallaPlataforma->SetWorldScale3D(FVector(1.5f, 0.5f, 0.4f));
}

void APlataforma::BeginPlay()
{
	Super::BeginPlay();
}

void APlataforma::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlataforma::AlImpactarConPelota()
{
	UE_LOG(LogTemp, Log, TEXT("Impacto en la plataforma base"));
}