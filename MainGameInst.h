// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MainGameInst.generated.h"

/**
 * 
 */
UCLASS()
class SEATEK_API UMainGameInst : public UGameInstance
{
	GENERATED_BODY()

	UMainGameInst();

public:

	UFUNCTION(BlueprintCallable)
	void SetupHUD();

	UFUNCTION(BlueprintCallable)
	void SetupMainMenu();

	UFUNCTION(BlueprintCallable)
	void SetupPauseMenu();

	UFUNCTION(BlueprintCallable)
	void SetupDeathMenu();

	UFUNCTION(BlueprintCallable)
	void SetupEndLevel();

	class UPlayerHud* GetPlayerHUD() { return current_playerhud; }
	class UEndLevel* GetEndLevel() { return current_endlevel; }

protected:

	virtual void Init() override;

	UPlayerHud* current_playerhud;

	UEndLevel* current_endlevel;

	TSubclassOf<class UPlayerHud> hud_class;

	TSubclassOf<class UMainMenu> mainmenu_class;
	
	TSubclassOf<class UPauseMenu> pausemenu_class;

	TSubclassOf<class UDeathMenu> deathmenu_class;


	TSubclassOf<class UEndLevel> endlevel_class;
	
};
