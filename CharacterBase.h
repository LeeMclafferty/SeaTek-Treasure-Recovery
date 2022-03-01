// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SeaTekCharacter.h"
#include "CharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class SEATEK_API ACharacterBase : public ASeaTekCharacter
{
	GENERATED_BODY()

	ACharacterBase();

public:

	UFUNCTION(BlueprintCallable)
	int32 GetScore() { return score; }
	UFUNCTION(BlueprintCallable)
	int32 GetHealth() { return health; }
	UFUNCTION(BlueprintCallable)
	int32 GetDamage() { return damage; }
	void SetScore(int32 value);

	UPROPERTY(BlueprintReadOnly, Category = "Movment")
	bool is_attacking;
	UPROPERTY(BlueprintReadOnly, Category = "Movment")
	bool is_dashing;
	UPROPERTY(BlueprintReadOnly, Category = "State")
	bool is_dead;
	float final_time;
protected:

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;

	void SetHealth(int32 value);
	void SetDamage(int32 value);

	void AddFriction();
	
	UFUNCTION()
	void Dash();

	UFUNCTION()
	void MoveUp(float value);
	UFUNCTION()
	void Attack();
	UFUNCTION()
	void OnPressPause();

	UFUNCTION()
	void HandleDeath();

	bool is_paused;

	int32 score;


	UPROPERTY(EditAnywhere, Category = "Combat")
	float attack_cooldown;
	float attack_check;

	UPROPERTY(EditAnywhere, Category = "Mobility")
	float dash_speed;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float dash_cooldown;
	float dash_check;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	class UNiagaraSystem* dash_VFX;

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	class UNiagaraSystem* take_damage_VFX;


	UPROPERTY(EditDefaultsOnly, Category = "SFX")
	class USoundCue* take_damage_SFX;

	UPROPERTY(EditDefaultsOnly, Category = "SFX")
	class USoundCue* enemy_hit_SFX; 

	int32 level_timer;
	float one_second;
	float one_second_check;
	
private:

	int32 health;
	int32 damage;


	
};
