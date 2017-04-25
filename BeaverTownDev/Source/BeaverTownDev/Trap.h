// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Trap.generated.h"


UCLASS()
class BEAVERTOWNDEV_API ATrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrap();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Sound")
		USoundBase* TriggerSound;
	UPROPERTY(EditAnywhere)
		ATriggerVolume* TrapTrigger = nullptr;
	UPROPERTY(EditAnywhere, Category = "Spawning")
		UClass* ObjectToSpawn = nullptr;

	bool TrapActive = true;

	void TrapTriggered();
	
};
