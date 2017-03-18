// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interact.h"
#include "FellableTree.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFellTree);

UCLASS()
class BEAVERTOWNDEV_API AFellableTree : public AInteract
{
	GENERATED_BODY()

public:
	// Constructor
	AFellableTree();

	virtual void OpenEvent() override;

	UPROPERTY(BlueprintAssignable)
		FFellTree TreeOpen;

	UPROPERTY(EditAnywhere)
		int32 Health = 100;	
};
