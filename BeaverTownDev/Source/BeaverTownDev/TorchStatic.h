// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "TorchStatic.generated.h"

UCLASS()
class BEAVERTOWNDEV_API ATorchStatic : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATorchStatic();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bIsLit;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
