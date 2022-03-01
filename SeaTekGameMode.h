// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SeaTekGameMode.generated.h"

UCLASS(minimalapi)
class ASeaTekGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASeaTekGameMode();

protected:


	virtual void BeginPlay() override;

};



