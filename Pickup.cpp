// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

#include "CharacterBase.h"

// Sets default values
APickup::APickup()
{

	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));

	static_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	static_mesh->SetupAttachment(RootComponent);
	static_mesh->SetCollisionProfileName("NoCollision");

	box_component = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	box_component->SetCollisionProfileName("Pickup");
	box_component->SetupAttachment(RootComponent);
	

	point_value = 1;

}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();


}


// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickup::PlaySound()
{
	if (pickup_cue)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), pickup_cue, GetActorLocation());
	}
}

