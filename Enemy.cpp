
#include "Enemy.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"

#include "CharacterBase.h"


AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));

	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(RootComponent);

	collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	collision->SetupAttachment(RootComponent);

	speed = 50.f;
	damage = 1;
	health = 1;
	point_value = 5;


}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	is_active = false;

	global_start_location = GetActorLocation();
	global_target_location = GetTransform().TransformPosition(target_location);
	
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
		FVector location = GetActorLocation();
			// How far enemy needs to move
		float travel_length = (global_target_location - global_start_location).Size();
			// How far it has moved
		float travled = (location - global_start_location).Size();

		if (travled >= travel_length)
		{	
				// Swaps the start and end points of vector once it has reached the end.
			FVector swap = global_start_location;
			global_start_location = global_target_location;
			global_target_location = swap;
			
			SetActorRotation(GetActorRotation() * (-1));
			
		}
			//Every frame update the actors location by its speed towards the target point.
		FVector direction = (global_target_location - location).GetSafeNormal();
		location += speed * DeltaTime * direction;
		SetActorLocation(location);


		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Purple, FString::Printf(TEXT("Enemy Rotation %s"), *GetActorRotation().ToString()));
	

}

void AEnemy::SetHealth(int32 value)
{
	health -= value;

	if(health <= 0)
	{ 
		Destroy();
		if (ACharacterBase* pawn = Cast<ACharacterBase>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
		{
			pawn->SetScore(GetPointValue());
		}

	}
}

void AEnemy::ActiveEnemyMovment()
{
	is_active = true;
}

