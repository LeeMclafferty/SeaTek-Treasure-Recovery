// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInst.h"
#include "Blueprint/WidgetLayoutLibrary.h"

#include "PlayerHud.h"
#include "SeaTekController.h"
#include "Kismet/GameplayStatics.h"
#include "MainMenu.h"
#include "DeathMenu.h"
#include "PauseMenu.h"
#include "CharacterBase.h"
#include "EndLevel.h"

UMainGameInst::UMainGameInst()
{
	static ConstructorHelpers::FClassFinder<UPlayerHud> playerhud_bpclass(TEXT("/Game/aa_Widgets/BP_PlayerHUD"));
	if (playerhud_bpclass.Class != NULL)
	{
		hud_class = playerhud_bpclass.Class;
	}
	static ConstructorHelpers::FClassFinder<UMainMenu> mainmenu_bpclass(TEXT("/Game/aa_Widgets/BP_MainMenu"));
	if (mainmenu_bpclass.Class != NULL)
	{
		mainmenu_class = mainmenu_bpclass.Class;
	}
	static ConstructorHelpers::FClassFinder<UPauseMenu> pausemenu_bpclass(TEXT("/Game/aa_Widgets/BP_PauseMenu"));
	if (pausemenu_bpclass.Class != NULL)
	{
		pausemenu_class = pausemenu_bpclass.Class;
	}
	static ConstructorHelpers::FClassFinder<UDeathMenu> deathmenu_bpclass(TEXT("/Game/aa_Widgets/BP_DeathMenu"));
	if (deathmenu_bpclass.Class != NULL)
	{
		deathmenu_class = deathmenu_bpclass.Class;
	}
	static ConstructorHelpers::FClassFinder<UEndLevel> endlevel_bpclass(TEXT("/Game/aa_Widgets/BP_EndLevelMenu"));
	if (endlevel_bpclass.Class != NULL)
	{
		endlevel_class = endlevel_bpclass.Class;
	}

}

void UMainGameInst::SetupHUD()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());

	if(hud_class != NULL)
	{ 
		if(ASeaTekController* pc = Cast<ASeaTekController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
		{
			if(ACharacterBase* pawn = Cast<ACharacterBase>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
			{
				UPlayerHud* hud = CreateWidget<UPlayerHud>(this, hud_class);
					current_playerhud = hud;
					hud->UpdateHearts();
					hud->SetPointsText(pawn->GetScore());
					hud->AddToViewport();

					FInputModeGameOnly input_data;
					pc->bShowMouseCursor = false;
					pc->SetInputMode(input_data);
			}
		}

	}
}

void UMainGameInst::SetupMainMenu()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
	if (mainmenu_class != NULL)
	{
		if (ASeaTekController* pc = Cast<ASeaTekController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
		{
			UMainMenu* menu = CreateWidget<UMainMenu>(this, mainmenu_class);
			menu->AddToViewport();

			FInputModeUIOnly input_data;
			pc->bShowMouseCursor = true;
			pc->SetInputMode(input_data);
		}

	}
}

void UMainGameInst::SetupPauseMenu()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
	if (pausemenu_class != NULL)
	{
		if (ASeaTekController* pc = Cast<ASeaTekController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
		{
			UPauseMenu* menu = CreateWidget<UPauseMenu>(this, pausemenu_class);
			menu->AddToViewport();

			FInputModeUIOnly input_data;
			pc->bShowMouseCursor = true;
			pc->SetInputMode(input_data);
		}

	}
}

void UMainGameInst::SetupDeathMenu()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
	if (deathmenu_class != NULL)
	{
		if (ASeaTekController* pc = Cast<ASeaTekController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
		{
			UDeathMenu* menu = CreateWidget<UDeathMenu>(this, deathmenu_class);
			menu->AddToViewport();

			FInputModeUIOnly input_data;
			pc->bShowMouseCursor = true;
			pc->SetInputMode(input_data);
		}

	}
}

void UMainGameInst::SetupEndLevel()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
	if (endlevel_class != NULL)
	{
		if (ASeaTekController* pc = Cast<ASeaTekController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
		{
			UEndLevel* menu = CreateWidget<UEndLevel>(this, endlevel_class);
			menu->AddToViewport();
			current_endlevel = menu;

			FInputModeUIOnly input_data;
			pc->bShowMouseCursor = true;
			pc->SetInputMode(input_data);
		}

	}
}

void UMainGameInst::Init()
{
	if (hud_class == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("HUD class not found"));
	}

	if (mainmenu_class == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("Main Menu class not found"));
	}

	if (pausemenu_class == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("Pause Menu class not found"));
	}

	if (deathmenu_class == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("Death Menu class not found"));
	}
	if (endlevel_class == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("End Level Menu class not found"));
	}
}
