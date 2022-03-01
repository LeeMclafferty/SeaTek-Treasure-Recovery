// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndLevel.generated.h"

/**
 * 
 */
UCLASS()
class SEATEK_API UEndLevel : public UUserWidget
{
	GENERATED_BODY()

		virtual bool Initialize() override;

public:

	UFUNCTION()
	void UpdateScore(float in_time, int32 in_score);

protected:

	UPROPERTY(meta = (BindWidget))
	class UButton* next_button;

	UPROPERTY(meta = (BindWidget))
	class UButton* quit_button;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* score_text;

	UFUNCTION()
	void OnPressQuit();

	UFUNCTION()
	void OnPressNext();


	

	
};
