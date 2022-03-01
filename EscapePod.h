// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EscapePod.generated.h"

UCLASS()
class SEATEK_API AEscapePod : public AActor
{
	GENERATED_BODY()
	
public:	
	AEscapePod();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* mesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* box_collision;

	void EndLevel();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
