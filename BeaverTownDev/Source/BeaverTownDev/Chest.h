// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interact.h"
#include "Chest.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTriggerEvent);

UCLASS()
class BEAVERTOWNDEV_API AChest : public AInteract
{
	GENERATED_BODY()

public:
	virtual void OpenEvent() override;
	virtual void CloseEvent() override;
	
	UPROPERTY(BlueprintAssignable)
		FTriggerEvent AlexOpen;
	UPROPERTY(BlueprintAssignable)
		FTriggerEvent AlexClose;
};
