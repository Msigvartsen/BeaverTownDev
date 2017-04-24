// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "EnemyAIController.h"
#include "EnemyAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyAIAttack.h"

EBTNodeResult::Type UEnemyAIAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIController* AIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	if (AIController)
	{
		AIController->Attack();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}


