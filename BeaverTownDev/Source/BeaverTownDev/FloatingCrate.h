// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "FloatingCrate.generated.h"

UCLASS()
class BEAVERTOWNDEV_API AFloatingCrate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingCrate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//UFUNCTION(BlueprintImplementableEvent, Category = "FloatingCrate")
	//	void MoveCrate();
	void MoveCrate(FVector Direction);

	UPROPERTY(EditAnywhere)
		USceneComponent* FloatingCrateRoot = nullptr;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* FloatingCrateMesh = nullptr;
	UPROPERTY(EditAnywhere)
		UArrowComponent* FloatingCrateArrow = nullptr;
	UPROPERTY(EditAnywhere)
		float Force = 150.f;

	UPrimitiveComponent* FloatingCratePrimitive = nullptr;
	
};