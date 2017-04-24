// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "StreamCollision.generated.h"

UCLASS()
class BEAVERTOWNDEV_API AStreamCollision : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStreamCollision();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		USceneComponent* StreamRoot = nullptr;
	UPROPERTY(EditAnywhere)
		UBoxComponent* StreamCollision = nullptr;
	UPROPERTY(EditAnywhere)
		UArrowComponent* StreamArrow = nullptr;
	UPROPERTY(EditAnywhere)
		bool bMakeFall = false;
	UPROPERTY(EditAnywhere)
		bool bStopFall = false;

private:
	UBoxComponent* Collision = nullptr;
	AFloatingCrate* Crate = nullptr;
	
	
};
