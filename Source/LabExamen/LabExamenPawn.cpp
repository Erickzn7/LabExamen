// Copyright Epic Games, Inc. All Rights Reserved.

#include "LabExamenPawn.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Pelota.h"

const FName ALabExamenPawn::MoveRightBinding("MoveRight");

ALabExamenPawn::ALabExamenPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CuboMesh(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	RootComponent = ShipMeshComponent;
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	ShipMeshComponent->SetNotifyRigidBodyCollision(true);

	if (CuboMesh.Succeeded())
	{
		ShipMeshComponent->SetStaticMesh(CuboMesh.Object);
	}

	ShipMeshComponent->SetWorldScale3D(FVector(0.5f, 2.0f, 0.4f));

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = 1500.0f;
	CameraBoom->SetRelativeRotation(FRotator(-80.0f, 0.0f, 0.0f));
	CameraBoom->bDoCollisionTest = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	MoveSpeed = 1200.0f;
	PelotaActiva = nullptr;
	bTeclaDisparoPresionada = false;
}

void ALabExamenPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	// Movimiento lateral
	PlayerInputComponent->BindAxis(MoveRightBinding, this, &ALabExamenPawn::MoverHorizontal);
}

void ALabExamenPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Detección directa de teclado/ratón desde el controlador (infalible ante configuraciones del proyecto)
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		const bool bEspacio = PC->IsInputKeyDown(EKeys::SpaceBar);
		const bool bClicIzquierdo = PC->IsInputKeyDown(EKeys::LeftMouseButton);
		const bool bEnter = PC->IsInputKeyDown(EKeys::Enter);
		const bool bTeclaI = PC->IsInputKeyDown(EKeys::I);

		if (bEspacio || bClicIzquierdo || bEnter || bTeclaI)
		{
			if (!bTeclaDisparoPresionada)
			{
				bTeclaDisparoPresionada = true;
				DispararPelota();
			}
		}
		else
		{
			bTeclaDisparoPresionada = false;
		}
	}
}

void ALabExamenPawn::MoverHorizontal(float Valor)
{
	if (Valor != 0.0f)
	{
		const FVector Desplazamiento = FVector(0.0f, Valor * MoveSpeed * GetWorld()->GetDeltaSeconds(), 0.0f);
		AddActorWorldOffset(Desplazamiento, true);
	}
}

void ALabExamenPawn::DispararPelota()
{
	// Solo dispara si no existe una pelota en juego (o si la anterior fue destruida)
	if (PelotaActiva == nullptr || !IsValid(PelotaActiva))
	{
		UWorld* const World = GetWorld();
		if (!World) return;

		// Spawn al frente del Pawn (en el eje X)
		const FVector SpawnLocation = GetActorLocation() + FVector(160.0f, 0.0f, 0.0f);

		// Inclinación inicial de 20 grados para evitar trayectorias en línea recta fija
		const FRotator SpawnRotation = FRotator(0.0f, 20.0f, 0.0f);

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();
		// OBLIGA A LA PELOTA A SPAWNEAR aunque toque levemente la colisión del pawn o piso
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		PelotaActiva = World->SpawnActor<APelota>(APelota::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
	}
}