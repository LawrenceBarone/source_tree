// Copyright Epic Games, Inc. All Rights Reserved.

#include "EscapeGameM1GameMode.h"
#include "EscapeGameM1Character.h"
#include "UObject/ConstructorHelpers.h"

AEscapeGameM1GameMode::AEscapeGameM1GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
