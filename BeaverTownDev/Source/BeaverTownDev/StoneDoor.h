// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "StoneDoor.generated.h"

UCLASS()
class BEAVERTOWNDEV_API AStoneDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStoneDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//UFUNCTION(BlueprintImplementableEvent, Category = "RollingDoor")
	//	void OpenDoor();
	//UFUNCTION(BlueprintImplementableEvent, Category = "RollingDoor")
	//	void CloseDoor();
	
};
