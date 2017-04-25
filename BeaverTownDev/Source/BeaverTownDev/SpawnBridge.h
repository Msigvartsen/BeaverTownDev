// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SpawnBridge.generated.h"

UCLASS()
class BEAVERTOWNDEV_API ASpawnBridge : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ASpawnBridge();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		class ATriggerVolume* BridgeTrigger = nullptr;

	UPROPERTY(EditAnywhere)
		int32 BridgeIndex;

	UPROPERTY(EditAnywhere)
		int32 PlayerCollectedWood;
protected:

	virtual void BeginPlay() override;

private:

	UStaticMeshComponent* BridgeMesh = nullptr;
	void BuildBridge();

	
	
};
