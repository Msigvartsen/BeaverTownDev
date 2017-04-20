// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ThrowableItems.generated.h"

UCLASS()
class BEAVERTOWNDEV_API AThrowableItems : public AActor
{
	GENERATED_BODY()
	
public:	
	AThrowableItems();

	virtual void Tick(float DeltaTime) override;

	void SetIsThrown(bool IsThrow);

	UFUNCTION()
		bool GetIsThrown() const { return IsThrown; }
	
protected:
	virtual void BeginPlay() override;

private:
	bool IsThrown = false;


	


};
