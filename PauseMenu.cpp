// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

#include "MainGameInst.h"


bool UPauseMenu::Initialize()
{
	bool success = Super::Initialize();

	if (continue_button)
	{
		continue_button->OnPressed.AddDynamic(this, &UPauseMenu::OnPressContinue);
	}
	if (quit_button)
	{
		quit_button->OnPressed.AddDynamic(this, &UPauseMenu::OnPressQuit);
	}
	return success;
}

void UPauseMenu::OnPressQuit()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
}

void UPauseMenu::OnPressContinue()
{
	this->RemoveFromParent();

	if (UMainGameInst* game_inst = Cast<UMainGameInst>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		game_inst->SetupHUD();
	}
}
