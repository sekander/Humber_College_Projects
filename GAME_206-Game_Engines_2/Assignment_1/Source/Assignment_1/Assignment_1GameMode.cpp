// Copyright Epic Games, Inc. All Rights Reserved.

#include "Assignment_1GameMode.h"
#include "Assignment_1Character.h"
#include "UObject/ConstructorHelpers.h"

AAssignment_1GameMode::AAssignment_1GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
