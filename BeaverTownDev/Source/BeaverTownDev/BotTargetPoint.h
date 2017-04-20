// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/TargetPoint.h"
#include "BotTargetPoint.generated.h"

/**
 * 
 */
UCLASS()
class BEAVERTOWNDEV_API ABotTargetPoint : public ATargetPoint
{
	GENERATED_BODY()
	
	
public:
	UPROPERTY(EditAnywhere,Category = "WaypointIndex")
		int32 WaypointIndex = 0;
	
	UFUNCTION()
	 int32 GetWaypointIndex() const { return WaypointIndex; }
};
