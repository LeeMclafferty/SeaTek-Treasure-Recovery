// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.h"
#include "MovmentTrigger.generated.h"

UCLASS()
class SEATEK_API AMovmentTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	AMovmentTrigger();
	
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* trigger_box;

	UPROPERTY(EditAnywhere)
	TArray <AEnemy*> enemies; 

protected:
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
