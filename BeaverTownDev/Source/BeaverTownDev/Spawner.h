// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class BEAVERTOWNDEV_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ResetTimer();

private:
	// Pointer to spawning class
	FTimerHandle TimerHandle;
	UPROPERTY(EditAnywhere, Category = "Spawning Options")
		float Time = 5.f;
	UPROPERTY(EditAnywhere, Category = "Spawning Options")
		float TimeUntilDestruction = 10.f;
	UPROPERTY(EditAnywhere, Category = "Spawning Options")
		float StartTimeDelay = 0.f;
	UPROPERTY(EditAnywhere, Category = "Spawning Options")
		bool bRandomRange = false;
	UPROPERTY(EditAnywhere, Category = "Spawning Options")
		float MaxX = 50.f;
	UPROPERTY(EditAnywhere, Category = "Spawning Options")
		float MinX = -50.f;
	UPROPERTY(EditAnywhere, Category = "Spawning Options")
		UClass* ObjectToSpawn = nullptr;
	UPROPERTY(EditAnywhere, Category = "Spawning Options")
		bool bLimitSpawning = false;
	UPROPERTY(EditAnywhere, Category = "Spawning Options")
		int SpawnLimit = 1;

	AActor *SpawnedActor = nullptr;
	FVector SpawnLocation;
	FRotator SpawnRotation;
	bool bCanSpawn = true;
	int ActorsSpawned = 0;
	

};
