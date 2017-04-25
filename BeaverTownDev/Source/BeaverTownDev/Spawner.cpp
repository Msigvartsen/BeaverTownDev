// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "MainCharacter.h"
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

	if (bRandomRange)
	{
		SpawnLocation = GetActorLocation() + (GetActorForwardVector() * FMath::FRandRange(MinX, MaxX));
	}
	else
	{
		SpawnLocation = GetActorLocation();
	}

	if (bCanSpawn && GetWorld()->GetTimeSeconds() > StartTimeDelay)
	{
		ActorsSpawned++;
		if (bLimitSpawning)
		{
			if (ActorsSpawned >= SpawnLimit)
			{
				bCanSpawn = false;
				return;
			}
		}
		bCanSpawn = false;
		
			
		if (ObjectToSpawn)
		{
			SpawnRotation = GetActorRotation();
			SpawnedActor = GetWorld()->SpawnActor<AActor>(ObjectToSpawn, SpawnLocation, SpawnRotation);
			SpawnedActor->SetLifeSpan(TimeUntilDestruction);
		}
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASpawner::ResetTimer, Time, false);
	}
}

void ASpawner::ResetTimer()
{
	bCanSpawn = true;
}
