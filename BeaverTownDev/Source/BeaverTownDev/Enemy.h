// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class BEAVERTOWNDEV_API AEnemy : public AActor
{
	GENERATED_BODY()
	
private:

	AEnemy();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere)
		USceneComponent* EnemyRoot = nullptr;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* EnemyMesh = nullptr;
	UPROPERTY(EditAnywhere)
		UShapeComponent* EnemyCollision = nullptr;
	
	
};
