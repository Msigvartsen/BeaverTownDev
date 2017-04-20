// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DamageVolume.generated.h"

class UMainGameInstance;

UCLASS()
class BEAVERTOWNDEV_API ADamageVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADamageVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		bool bPeriodicDamage = false;
	UPROPERTY(EditAnywhere)
		float DPS = 10.f;
	UPROPERTY(EditAnywhere)
		float SingleDamage = 100.f;
	UPROPERTY(EditAnywhere)
		USceneComponent* Root = nullptr;
	UPROPERTY(EditAnywhere)
		UBoxComponent* Box = nullptr;

private:
	UMainGameInstance* GameInstance = nullptr;
		
	
};
