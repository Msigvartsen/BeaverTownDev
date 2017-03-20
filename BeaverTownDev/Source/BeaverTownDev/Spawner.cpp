// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "Spawner.h"


// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("MyRoot"));
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bCanSpawn)
	{
		bCanSpawn = false;
		if (ObjectToSpawn)
		{
			FVector SpawnLocation = GetActorLocation();
			FRotator SpawnRotation = GetActorRotation();
			SpawnedActor = GetWorld()->SpawnActor<AActor>(ObjectToSpawn, SpawnLocation, SpawnRotation);
		}
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASpawner::ResetTimer, Time, false);
	}

}

void ASpawner::ResetTimer()
{
	SpawnedActor->Destroy();
	bCanSpawn = true;
}

