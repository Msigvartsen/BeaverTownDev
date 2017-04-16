// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "TargetPointSelectionTask.generated.h"

/**
 * 
 */
UCLASS()
class BEAVERTOWNDEV_API UTargetPointSelectionTask : public UBTTaskNode
{
	GENERATED_BODY()
	
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	
};
