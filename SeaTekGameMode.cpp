// Copyright Epic Games, Inc. All Rights Reserved.

#include "SeaTekGameMode.h"
#include "SeaTekCharacter.h"
#include "UObject/ConstructorHelpers.h"

#include "PlayerHud.h"

ASeaTekGameMode::ASeaTekGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}


}

void ASeaTekGameMode::BeginPlay()
{
	//UPlayerHud* hud = CreateWidget<UPlayerHud>(this, hud_class);
}
