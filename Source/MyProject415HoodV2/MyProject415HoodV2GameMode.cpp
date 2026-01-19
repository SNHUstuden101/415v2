// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProject415HoodV2GameMode.h"
#include "MyProject415HoodV2Character.h"
#include "UObject/ConstructorHelpers.h"

AMyProject415HoodV2GameMode::AMyProject415HoodV2GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
