// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "BotTargetPoint.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TargetPointSelectionTask.h"


EBTNodeResult::Type UTargetPointSelectionTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIController* AIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());

	if (AIController)
	{
		UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComp();
		ABotTargetPoint* CurrentPoint = Cast<ABotTargetPoint>(BlackboardComp->GetValueAsObject("LocationToGo"));

		TArray<AActor*> AvailableTargetPoints = AIController->GetAvailableTargetPoints();

		int32 RandomIndex;

		//Store next possible target point
		ABotTargetPoint* NextTargetPoint = nullptr;

		do {
			RandomIndex = FMath::RandRange(0, AvailableTargetPoints.Num() - 1);

			NextTargetPoint = Cast<ABotTargetPoint>(AvailableTargetPoints[RandomIndex]);
		} while (CurrentPoint == NextTargetPoint);

		//Update value of blackboard key
		BlackboardComp->SetValueAsObject("LocationToGo", NextTargetPoint);
		
		//return Successfull task
		AIController->GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = 150.f;
		return EBTNodeResult::Succeeded;
	}

	//Return failed task
	return EBTNodeResult::Failed;
}


