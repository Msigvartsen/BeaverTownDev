// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interact.h"
#include "HealthPickups.generated.h"

/**
 * 
 */
UCLASS()
class BEAVERTOWNDEV_API AHealthPickups : public AInteract
{
	GENERATED_BODY()

public:
	AHealthPickups();
	float HealTarget();
protected:
		virtual void BeginPlay() override;

private:
	

	UPROPERTY(EditAnywhere,Category="Healing")
	float HealingApplied = 40.f;
	
	
	
	
};
