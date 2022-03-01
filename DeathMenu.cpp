// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathMenu.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

#include "MainGameInst.h"


bool UDeathMenu::Initialize()
{
	bool success = Super::Initialize();

	if (quit_button)
	{
		quit_button->OnPressed.AddDynamic(this, &UDeathMenu::OnPressQuit);
	}
	if (restart_button)
	{
		restart_button->OnPressed.AddDynamic(this, &UDeathMenu::OnPressRestart);
	}

	return success;
}

void UDeathMenu::OnPressQuit()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
}

void UDeathMenu::OnPressRestart()
{

	FName level_name = *GetWorld()->GetName();

	UGameplayStatics::OpenLevel(GetWorld(), level_name, false);
	
}
