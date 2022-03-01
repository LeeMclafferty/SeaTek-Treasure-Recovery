// Fill out your copyright notice in the Description page of Project Settings.


#include "EndLevel.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Image.h"
#include "Components/Button.h"

#include "CharacterBase.h"

bool UEndLevel::Initialize()
{
	bool success = Super::Initialize();

	if (quit_button)
	{
		quit_button->OnPressed.AddDynamic(this, &UEndLevel::OnPressQuit);
	}
	if (next_button)
	{
		next_button->OnPressed.AddDynamic(this, &UEndLevel::OnPressNext);
	}

	return success;
}

void UEndLevel::OnPressQuit()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
}

void UEndLevel::OnPressNext()
{
	FName level_name = *GetWorld()->GetName();

	if (level_name == "LevelOne")
		UGameplayStatics::OpenLevel(GetWorld(), "/Game/AA_Maps/LevelTwo");
	else
	{
		OnPressQuit();
	}
}

void UEndLevel::UpdateScore(float in_time, int32 in_score)
{
	if (ACharacterBase* pawn = Cast<ACharacterBase>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		int32 time = (int32)in_time;
		
		

		FString score_string = FString::FromInt(time / in_score);
		score_text->SetText(FText::FromString(score_string));

	}
}
