// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Widget.h"
#include "SeaTekController.h"


bool UMainMenu::Initialize()
{
	bool success  = Super::Initialize();

	if (start_button)
	{
		start_button->OnPressed.AddDynamic(this, &UMainMenu::OnPressStartButton);
	}
	if (quit_button)
	{
		quit_button->OnPressed.AddDynamic(this, &UMainMenu::OnPressQuitButton);
	}
	if (quit_button_1)
	{
		quit_button_1->OnPressed.AddDynamic(this, &UMainMenu::OnPressQuitButton);
	}
	if (level_1_button)
	{
		level_1_button->OnPressed.AddDynamic(this, &UMainMenu::OnPressLevelOneButton);
	}
	if (level_2_button)
	{
		level_2_button->OnPressed.AddDynamic(this, &UMainMenu::OnPressLevelTwoButton);
	}
	if (level_3_button)
	{
		level_3_button->OnPressed.AddDynamic(this, &UMainMenu::OnPressLevelThreeButton);
	}
	if (level_4_button)
	{
		level_4_button->OnPressed.AddDynamic(this, &UMainMenu::OnPressLevelFourButton);
	}
	if (level_5_button)
	{
		level_5_button->OnPressed.AddDynamic(this, &UMainMenu::OnPressLevelFiveButton);
	}


	return success;
}

void UMainMenu::OnPressStartButton()
{
	menu_switcher->SetActiveWidget(level_menu);
}

void UMainMenu::OnPressQuitButton()
{
	if(ASeaTekController* pc = Cast<ASeaTekController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{ 
		UKismetSystemLibrary::QuitGame(GetWorld(), pc, EQuitPreference::Quit, false);
	}
}

void UMainMenu::OnPressLevelOneButton()
{
	UGameplayStatics::OpenLevel(GetWorld(), "/Game/AA_Maps/LevelOne");
}

void UMainMenu::OnPressLevelTwoButton()
{
	UGameplayStatics::OpenLevel(GetWorld(), "/Game/AA_Maps/LevelTwo");
}

void UMainMenu::OnPressLevelThreeButton()
{
	//UGameplayStatics::OpenLevel(GetWorld(), "/Game/AA_Maps/LevelThree");
}

void UMainMenu::OnPressLevelFourButton()
{
	//UGameplayStatics::OpenLevel(GetWorld(), "/Game/AA_Maps/LevelFour");
}

void UMainMenu::OnPressLevelFiveButton()
{
	//UGameplayStatics::OpenLevel(GetWorld(), "/Game/AA_Maps/LevelFive");
}
