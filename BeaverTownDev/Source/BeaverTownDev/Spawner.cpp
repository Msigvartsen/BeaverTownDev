// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "MainCharacter.h"
#include "Spawner.h"


ASpawner::ASpawner()
{

	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("MyRoot"));
}

void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

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
