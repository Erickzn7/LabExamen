// Copyright Epic Games, Inc. All Rights Reserved.

#include "LabExamenGameMode.h"
#include "LabExamenPawn.h"

ALabExamenGameMode::ALabExamenGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = ALabExamenPawn::StaticClass();
}

