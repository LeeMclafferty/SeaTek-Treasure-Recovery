// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h" 
#include "Kismet/GameplayStatics.h"


#include "Pickup.h"
#include "Enemy.h"
#include "MovmentTrigger.h"
#include "EnviormentHazard.h"
#include "PlayerHud.h"
#include "MainGameInst.h"
#include "EscapePod.h"

#include "EndLevel.h"

ACharacterBase::ACharacterBase()
{
	GetCameraBoom()->SetRelativeRotation(FRotator(0.f , -90.f , 0.f));
	GetCameraBoom()->bUsePawnControlRotation = false;
	GetCameraBoom()->TargetArmLength = 700.f;
	GetCameraBoom()->TargetOffset = FVector(0.f, 0.f, 200.f);
	GetCameraBoom()->bInheritYaw = false;
	
	score = 0;
	health = 3;
	damage = 1;
	is_attacking = false;
	attack_cooldown = .5f;
	dash_cooldown = .3;
	dash_speed = 500.f;
	is_paused = false;
	is_dead = false;
	level_timer = 0;
	one_second = 1.f;

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACharacterBase::OnOverlapBegin);
	
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	level_timer = 0;
}

void ACharacterBase::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveUp", this, &ACharacterBase::MoveUp);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ACharacterBase::Attack);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &ACharacterBase::Dash); 
	PlayerInputComponent->BindAction("PauseMenu", IE_Pressed, this, &ACharacterBase::OnPressPause);

}

void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->TimeSince(attack_check) > attack_cooldown && is_attacking)
	{
		is_attacking = false;
	}
	if (GetWorld()->TimeSince(dash_check) > dash_cooldown && is_dashing)
	{
		is_dashing = false;
	}
	if (UMainGameInst* game_inst = Cast<UMainGameInst>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		if(GetWorld()->TimeSince(one_second_check) > one_second)
		{ 
			level_timer++;
			UPlayerHud* hud = game_inst->GetPlayerHUD();
			hud->UpdateTimer(level_timer);
			one_second_check = GetWorld()->GetTimeSeconds();
		}
	}
}

void ACharacterBase::SetHealth(int32 value)
{
	health -= value;
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Purple, FString::Printf(TEXT("Health: %i"), GetHealth()));

	if (UMainGameInst* game_inst = Cast<UMainGameInst>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		UPlayerHud* hud = game_inst->GetPlayerHUD();
		hud->UpdateHearts();
	}
}

void ACharacterBase::MoveUp(float value)
{
	if ((Controller != nullptr) && (value != 0.0f))
	{
		// find out which way is Up
		const FVector up_vector = GetMesh()->GetUpVector();

		if(is_moving_right)
		{ 
			GetMesh()->SetWorldRotation(FRotator(0, -90, 0));
			forward_arrow->SetWorldRotation(FRotator(0, 0, 0));

		}

		if(!is_moving_right)
		{ 
			GetMesh()->SetWorldRotation(FRotator(0, 90, 0));
			forward_arrow->SetWorldRotation(FRotator(0, -180, 0));
		}

		// add movement in that direction
		AddMovementInput(up_vector, value);
	}
}

void ACharacterBase::SetScore(int32 value)
{
	score += value;

	if (UMainGameInst* game_inst = Cast<UMainGameInst>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		UPlayerHud* hud = game_inst->GetPlayerHUD();
		hud->SetPointsText(score);
	}
}

void ACharacterBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (APickup* pickup = Cast<APickup>(OtherActor))
	{
		SetScore(pickup->point_value);
		if (pickup->pickup_VFX != NULL)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), pickup->pickup_VFX, pickup->GetActorLocation());
		}
		if (pickup->pickup_cue != NULL)
		{

			pickup->PlaySound();
		}

		pickup->Destroy();
		
	}

	if (AMovmentTrigger* move_trigger = Cast<AMovmentTrigger>(OtherActor))
	{
		for (int i = 0; i < move_trigger->enemies.Num(); i++)
		{
			move_trigger->enemies[i]->ActiveEnemyMovment();
		}
	}

	if (AEnemy* enemy = Cast<AEnemy>(OtherActor))
	{
		//Do Damage
		// Play hit animation
		// play hit particle
		// Check for death

		SetHealth(enemy->GetDamage());
		
		if(GetHealth() <= 0)
		{ 
			HandleDeath();
		}

		UGameplayStatics::PlaySoundAtLocation(GetWorld(), take_damage_SFX, GetActorLocation());
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), take_damage_VFX, GetActorLocation());

	}

	if (AEnviormentHazard* hazard = Cast<AEnviormentHazard>(OtherActor))
	{
		SetHealth(hazard->GetDamage());

		UGameplayStatics::PlaySoundAtLocation(GetWorld(), take_damage_SFX, GetActorLocation());

		if (GetHealth() <= 0)
			HandleDeath();
	}

	if (AEscapePod* pod = Cast<AEscapePod>(OtherActor))
	{
		final_time = level_timer;

		UMainGameInst* game_inst = Cast<UMainGameInst>(UGameplayStatics::GetGameInstance(GetWorld()));
		
		game_inst->SetupEndLevel();
		UEndLevel* end_menu = game_inst->GetEndLevel();
		end_menu->UpdateScore(final_time, GetScore());
		
	
		//pod->EndLevel();
	}

	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Purple, FString::Printf(TEXT("")));
}
void ACharacterBase::Attack()
{
	if(!is_attacking)
	{ 
		is_attacking = true;
		float reach = 500.f;
		const FRotator YawRotation(0, 0, 0);

		FHitResult hit;
		FVector start = forward_arrow->GetComponentLocation();
		FVector end = (forward_arrow->GetComponentLocation() + (forward_arrow->GetForwardVector() * reach));
		FCollisionQueryParams params;
		params.AddIgnoredActor(this);
		FCollisionResponseParams response;


		bool is_hit = GetWorld()->LineTraceSingleByChannel(hit, start, end, ECC_GameTraceChannel2, params);
		DrawDebugLine(GetWorld(), start, end, FColor::Purple, false, 5.f, ECC_GameTraceChannel2, 1.f);

		if (AEnemy* enemy = Cast<AEnemy>(hit.GetActor()))
		{
			enemy->SetHealth(damage);

			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Purple, FString::Printf(TEXT("Enemy HP %i"), enemy->GetHealth()));

			
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), enemy_hit_SFX, GetActorLocation());
		
		}

		attack_check = GetWorld()->GetTimeSeconds();
	}
}

void ACharacterBase::OnPressPause()
{
		UMainGameInst* game_inst = Cast<UMainGameInst>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!is_paused)
	{
		is_paused = true; 
		game_inst->SetupPauseMenu();
	}
	else {
		is_paused = false;
		game_inst->SetupHUD();
	}
}

void ACharacterBase::HandleDeath()
{
	GetCapsuleComponent()->SetCollisionProfileName("BlockAll");
	is_dead = true;
	
	if (UMainGameInst* game_inst = Cast<UMainGameInst>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		game_inst->SetupDeathMenu();
	}

}

void ACharacterBase::Dash()
{
	FTimerHandle friction_timer;

	if(!is_dashing)
	{ 
		const FVector forward_direction = forward_arrow->GetForwardVector();

	/*	LaunchCharacter(GetActorUpVector() * 500, false, false);
		LaunchCharacter(forward_direction * dash_speed, false, false);
		GetCharacterMovement()->SetMovementMode(MOVE_Swimming);*/

		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), dash_VFX, GetActorLocation(), forward_direction.Rotation() - FRotator(0, -180, 0));

			//Set Max swim speed for illusion of dash
		GetCharacterMovement()->MaxSwimSpeed = dash_speed;

		GetWorld()->GetTimerManager().SetTimer(friction_timer, this, &ACharacterBase::AddFriction, .5, false);

		is_dashing = true;
		dash_check = GetWorld()->GetTimeSeconds();

	}

}

void ACharacterBase::AddFriction()
{
	GetCharacterMovement()->Velocity = GetVelocity() / 2;
	GetCharacterMovement()->MaxSwimSpeed = 1000;
}




