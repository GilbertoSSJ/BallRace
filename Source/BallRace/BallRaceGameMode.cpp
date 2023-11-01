// Copyright Epic Games, Inc. All Rights Reserved.

#include "BallRaceGameMode.h"
#include "BallRaceCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABallRaceGameMode::ABallRaceGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
