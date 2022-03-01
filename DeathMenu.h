// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DeathMenu.generated.h"

/**
 * 
 */
UCLASS()
class SEATEK_API UDeathMenu : public UUserWidget
{
	GENERATED_BODY()

	virtual bool Initialize() override;

protected:

	UPROPERTY(meta = (BindWidget))
	class UButton* restart_button;

	UPROPERTY(meta = (BindWidget))
	class UButton* quit_button;

	UFUNCTION()
	void OnPressQuit();

	UFUNCTION()
	void OnPressRestart();
	
};
