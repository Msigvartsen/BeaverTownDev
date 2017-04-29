// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Trap.generated.h"


UCLASS()
class BEAVERTOWNDEV_API ATrap : public AActor
{
	GENERATED_BODY()
	
public:	
	ATrap();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	//SoundFX when the trap is triggered
	UPROPERTY(EditAnywhere, Category = "Trap")
		USoundBase* TriggerSound;
	//TriggerVolume in editor
	UPROPERTY(EditAnywhere,Category = "Trap")
		ATriggerVolume* TrapTrigger = nullptr;
	//Choose object to spawn
	UPROPERTY(EditAnywhere, Category = "Trap")
		UClass* ObjectToSpawn = nullptr;
	//How lifetime of actor before destroyed
	UPROPERTY(EditAnywhere)
		float Lifetime = 0;

	bool TrapActive = true;
	
	void TrapTriggered();
	
};
