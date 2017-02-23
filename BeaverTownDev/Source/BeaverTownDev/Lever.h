// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interact.h"
#include "Lever.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLeverTriggerEvent);

class APickup;
class AChest;

UCLASS()
class BEAVERTOWNDEV_API ALever : public AInteract
{
	GENERATED_BODY()
	
public:
	// Constructor
	ALever();

	virtual void OpenEvent() override;
	virtual void CloseEvent() override;

	UPROPERTY(BlueprintAssignable)
		FLeverTriggerEvent LeverOpen;
	UPROPERTY(BlueprintAssignable)
		FLeverTriggerEvent LeverClose;
	UPROPERTY(EditAnywhere, Category = Setup)
		TSubclassOf<AChest> SpawnBlueprint;
	AChest* Spawn = nullptr;
};
