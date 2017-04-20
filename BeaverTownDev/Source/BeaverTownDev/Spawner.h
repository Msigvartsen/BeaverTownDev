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
	UPROPERTY(EditAnywhere)
		float Time = 5.f;
	UPROPERTY(EditAnywhere)
		float TimeUntilDestruction = 10.f;
	UPROPERTY(EditAnywhere)
		float StartTimeDelay = 0.f;
	UPROPERTY(EditAnywhere)
		bool bRandomRange = false;
	UPROPERTY(EditAnywhere)
		float MaxX = 50.f;
	UPROPERTY(EditAnywhere)
		float MinX = -50.f;
	UPROPERTY(EditAnywhere, Category = "Spawning")
		UClass* ObjectToSpawn = nullptr;

	AActor *SpawnedActor = nullptr;
	FVector SpawnLocation;
	FRotator SpawnRotation;
	bool bCanSpawn = true;
	

};
