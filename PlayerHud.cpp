 // Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHud.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Image.h"

#include "CharacterBase.h"


bool UPlayerHud::Initialize()
{
	bool success = Super::Initialize();

	if (points_text)
	{
		points_text->SetText(FText::FromString("0"));
	}

	return success;
}

void UPlayerHud::SetPointsText(int32 new_points)
{
	FString points_string = FString::FromInt(new_points);
	points_text->SetText(FText::FromString(points_string));
}

void UPlayerHud::UpdateHearts()
{
	ACharacterBase* pawn = Cast<ACharacterBase>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (pawn != nullptr)
	{
		if (pawn->GetHealth() == 2)
		{
			heart03_image->SetVisibility(ESlateVisibility::Hidden);
		}
		if (pawn->GetHealth() == 1)
		{
			heart03_image->SetVisibility(ESlateVisibility::Hidden);
			heart02_image->SetVisibility(ESlateVisibility::Hidden);
		}
		if (pawn->GetHealth() == 0)
		{
			heart03_image->SetVisibility(ESlateVisibility::Hidden);
			heart02_image->SetVisibility(ESlateVisibility::Hidden);
			Heart01_image->SetVisibility(ESlateVisibility::Hidden);
		}
	}

}

void UPlayerHud::UpdateTimer(int in_timer)
{
	FString text_string = FString::FromInt(in_timer);
	timer_text->SetText(FText::FromString(text_string));
}


