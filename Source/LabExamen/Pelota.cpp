#include "Pelota.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Plataforma.h"

APelota::APelota()
{
	PrimaryActorTick.bCanEverTick = false;

	// 1. Componente de colision raiz (Nombres unicos para evitar conflicto en Obj.cpp)
	ColisionEsfera = CreateDefaultSubobject<USphereComponent>(TEXT("ColisionEsferaPelota"));
	ColisionEsfera->InitSphereRadius(25.0f);
	ColisionEsfera->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	ColisionEsfera->SetNotifyRigidBodyCollision(true);
	RootComponent = ColisionEsfera;

	// 2. Malla visual acoplada a la esfera
	MallaPelota = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaVisualPelota"));
	MallaPelota->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> EsferaMesh(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (EsferaMesh.Succeeded())
	{
		MallaPelota->SetStaticMesh(EsferaMesh.Object);
	}
	MallaPelota->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
	MallaPelota->SetCollisionEnabled(ECollisionEnabled::NoCollision); // La colision la maneja la esfera

	// 3. Configuración del movimiento de rebote infinito
	MovimientoProyectil = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovimientoPelota"));
	MovimientoProyectil->UpdatedComponent = RootComponent;
	MovimientoProyectil->InitialSpeed = 1200.0f;
	MovimientoProyectil->MaxSpeed = 1200.0f;
	MovimientoProyectil->bRotationFollowsVelocity = true;
	MovimientoProyectil->bShouldBounce = true;
	MovimientoProyectil->Bounciness = 1.0f;           // Rebote 100% elastico (sin perder energia)
	MovimientoProyectil->Friction = 0.0f;             // Sin friccion
	MovimientoProyectil->ProjectileGravityScale = 0.0f; // Sin gravedad hacia abajo

	// Restringir el movimiento al plano 2D (XY) para evitar desviaciones en el eje Z
	MovimientoProyectil->bConstrainToPlane = true;
	MovimientoProyectil->SetPlaneConstraintNormal(FVector(0.0f, 0.0f, 1.0f));

	// Enlace de colision con plataformas
	ColisionEsfera->OnComponentHit.AddDynamic(this, &APelota::AlImpactar);
}

void APelota::BeginPlay()
{
	Super::BeginPlay();
}

void APelota::AlImpactar(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this)
	{
		// Si impacta contra una plataforma, ejecuta su polimorfismo
		APlataforma* PlataformaImpactada = Cast<APlataforma>(OtherActor);
		if (PlataformaImpactada)
		{
			PlataformaImpactada->AlImpactarConPelota();
		}
	}
}