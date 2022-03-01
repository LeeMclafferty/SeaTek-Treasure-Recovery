// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class SEATEK_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	APickup();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* static_mesh;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* box_component;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	int32 point_value;
	
	UPROPERTY(EditDefaultsOnly, Category = "FX")
	class UNiagaraSystem* pickup_VFX;

	UPROPERTY(EditDefaultsOnly, Category = "FX")
	class USoundCue* pickup_cue;

	void PlaySound();


protected:
	virtual void BeginPlay() override;
	


};
