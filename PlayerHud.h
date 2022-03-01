// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHud.generated.h"

/**
 * 
 */
UCLASS()
class SEATEK_API UPlayerHud : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual bool Initialize() override;

	void SetPointsText(int32 new_points);

	void UpdateHearts();

	void UpdateTimer(int in_timer);
protected:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* points_text;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* timer_text;

	UPROPERTY(meta = (BindWidget))
	class UImage* Heart01_image;
	
	UPROPERTY(meta = (BindWidget))
	class UImage* heart02_image;

	UPROPERTY(meta = (BindWidget))
	class UImage* heart03_image;
	
};
