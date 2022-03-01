// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class SEATEK_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

	virtual bool Initialize() override;
	
public:

protected:

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* menu_switcher;

	UPROPERTY(meta = (BindWidget))
	class UWidget* start_menu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* level_menu;

		// Main Menu
	UPROPERTY(meta = (BindWidget))
	class UButton* start_button;

	UPROPERTY(meta = (BindWidget))
	class UButton* quit_button;

		//Level Menu
	UPROPERTY(meta = (BindWidget))
	class UButton* quit_button_1;

	UPROPERTY(meta = (BindWidget))
	class UButton* level_1_button;

	UPROPERTY(meta = (BindWidget))
	class UButton* level_2_button;

	UPROPERTY(meta = (BindWidget))
	class UButton* level_3_button;

	UPROPERTY(meta = (BindWidget))
	class UButton* level_4_button;

	UPROPERTY(meta = (BindWidget))
	class UButton* level_5_button;

		//On Pressed
	UFUNCTION()
	void OnPressStartButton();
	UFUNCTION()
	void OnPressQuitButton();
	UFUNCTION()
	void OnPressLevelOneButton();
	UFUNCTION()
	void OnPressLevelTwoButton();
	UFUNCTION()
	void OnPressLevelThreeButton();
	UFUNCTION()
	void OnPressLevelFourButton();
	UFUNCTION()
	void OnPressLevelFiveButton();
};
