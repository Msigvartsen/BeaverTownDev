// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Interact.generated.h"

UCLASS()
class BEAVERTOWNDEV_API AInteract : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteract();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OpenEvent();
	virtual void CloseEvent();
	bool GetIsOpenEvent();
	bool GetOnlyInteractFromAngle();
	float GetMaxOpenAngle();
	float GetMinOpenAngle();

protected:
	bool bIsOpenEvent = false;
	bool bOnlyInteractFromAngle = false;
	UPROPERTY(EditAnywhere)
		float MaxOpenAngle = 0;
	UPROPERTY(EditAnywhere)
		float MinOpenAngle = 0;
private:
	UPROPERTY(EditAnywhere)
		USceneComponent * MainRoot = nullptr;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent * BaseMesh = nullptr;

	
};
