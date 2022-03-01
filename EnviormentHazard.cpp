// Fill out your copyright notice in the Description page of Project Settings.


#include "EnviormentHazard.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
AEnviormentHazard::AEnviormentHazard()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));

	static_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	static_mesh->SetCollisionProfileName("NoCollision");
	static_mesh->SetupAttachment(RootComponent);

	collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	collision->SetupAttachment(RootComponent);
	collision->SetCollisionProfileName("NoCollision", false);

	damage = 1;
	cooldown = 10;
	damage_duration = 1.2f;

}

void AEnviormentHazard::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnviormentHazard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->TimeSince(cooldown_check) > cooldown)
	{
		GetWorld()->GetTimerManager().ClearTimer(cooldown_timer);
		ActivateDamage();
	}

}

void AEnviormentHazard::ActivateDamage()
{

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), particles, GetActorLocation());
	collision->SetCollisionProfileName("OverlapAll", true);
	cooldown_check = GetWorld()->GetTimeSeconds();

	GetWorld()->GetTimerManager().SetTimer(cooldown_timer, this, &AEnviormentHazard::DeactivateDamage, damage_duration, false);

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), bubble_SFX, GetActorLocation());
}

void AEnviormentHazard::DeactivateDamage()
{
	collision->SetCollisionProfileName("NoCollision", false);
}

