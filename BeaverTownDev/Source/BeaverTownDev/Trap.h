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


	UPROPERTY(EditAnywhere)
		USceneComponent* TrapRoot = nullptr;
	UPROPERTY(EditAnywhere)
		ATriggerVolume* TrapTrigger = nullptr;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* TrapMesh = nullptr;

	bool TrapActive = true;

	void TrapTriggered();

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AProjectile> ProjectileBlueprint;
	
};
