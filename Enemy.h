// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class SEATEK_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemy();
	virtual void Tick(float DeltaTime) override;

	float GetSpeed() { return speed; }
	int32 GetPointValue() { return point_value; }
	int32 GetDamage() { return damage; }
	int32 GetHealth() { return health; }

	void SetHealth(int32 value);

	UPROPERTY(EditAnywhere, Category = "Mobility", meta = (MakeEditWidget = true))
	FVector target_location;

	UFUNCTION(BlueprintCallable, Category = "Trigger")
	void ActiveEnemyMovment();

		// I will come back and change this to a skeletal mesh once I do the game art. 
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USkeletalMeshComponent* mesh;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCapsuleComponent* collision;


protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Mobility")
	float speed;

	UPROPERTY(EditAnywhere, Category = "Damage")
	int32 damage;

	UPROPERTY(EditAnywhere, Category = "Damage")
	int32 point_value;

	UPROPERTY(EditAnywhere, Category = "Damage")
	int32 health;

	bool is_active;
	
private:

	FVector global_start_location;
	FVector global_target_location;

};
