// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"

/**
 * 
 */
UCLASS()
class SEATEK_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()

	virtual bool Initialize() override;

protected:

	UPROPERTY(meta = (BindWidget))
	class UButton* continue_button;

	UPROPERTY(meta = (BindWidget))
	class UButton* quit_button;

	UFUNCTION()
	void OnPressQuit();

	UFUNCTION()
	void OnPressContinue();
	
};
