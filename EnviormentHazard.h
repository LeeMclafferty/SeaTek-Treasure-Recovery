// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnviormentHazard.generated.h"

UCLASS()
class SEATEK_API AEnviormentHazard : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnviormentHazard();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	class UNiagaraSystem* particles;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* static_mesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* collision;

	UFUNCTION()
	void ActivateDamage();

	UFUNCTION()
	void DeactivateDamage();

	int32 GetDamage() { return damage; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Damage")
	int32 damage; 

	UPROPERTY(EditAnywhere, Category = "Damage")
	float cooldown;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float damage_duration;

	FTimerHandle cooldown_timer;

	float cooldown_check;

	UPROPERTY(EditDefaultsOnly, Category = "SFX")
	class USoundCue* bubble_SFX;


};
