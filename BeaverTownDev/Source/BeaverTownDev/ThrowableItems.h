// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ThrowableItems.generated.h"

UCLASS()
class BEAVERTOWNDEV_API AThrowableItems : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThrowableItems();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UBoxComponent* BoxCollision = nullptr;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MyMesh = nullptr;


	void SetIgnorePlayerCollision(bool bTrue);
	
};
