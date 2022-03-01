

#include "MovmentTrigger.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"

AMovmentTrigger::AMovmentTrigger()
{

	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));

	trigger_box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	trigger_box->SetupAttachment(RootComponent);

}

void AMovmentTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMovmentTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

