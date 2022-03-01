// Fill out your copyright notice in the Description page of Project Settings.


#include "EscapePod.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEscapePod::AEscapePod()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	mesh->SetupAttachment(RootComponent);

	box_collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	box_collision->SetupAttachment(RootComponent);

}

void AEscapePod::EndLevel()
{
	FName level_name = *GetWorld()->GetName();

	if(level_name == "LevelOne")
		UGameplayStatics::OpenLevel(GetWorld(), "/Game/AA_Maps/LevelTwo");
	if(level_name == "LevelTwo")
		UGameplayStatics::OpenLevel(GetWorld(), "/Game/AA_Maps/LevelThree");
	if(level_name == "LevelThree")
		UGameplayStatics::OpenLevel(GetWorld(), "/Game/AA_Maps/LevelFour");
	if(level_name == "LevelFour")
		UGameplayStatics::OpenLevel(GetWorld(), "/Game/AA_Maps/LevelFive");

	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Purple, FString::Printf(TEXT("%s"), *level_name.ToString()));
}

void AEscapePod::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEscapePod::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

