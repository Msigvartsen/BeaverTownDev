// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BotTargetPoint.h"
#include "EnemyAI.h"
#include "MainCharacter.h"
#include "MainGameInstance.h"
#include "EnemyAIController.h"


AEnemyAIController::AEnemyAIController()
{
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	LocationToGoKey = "LocationToGo";
}

void AEnemyAIController::Possess(APawn* Pawn)
{
	Super::Possess(Pawn);

	EnemyAI = Cast<AEnemyAI>(Pawn);

	if (EnemyAI)
	{
		//Initialize blackboard if blackboard is valid.
		if (EnemyAI->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*(EnemyAI->BehaviorTree->BlackboardAsset));
			
		}
		//Finds all actors of set class, and puts them into an Array (BotTargetPoints) 
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABotTargetPoint::StaticClass(), BotTargetPoints);

		//Starts BehaviorTree
		BehaviorComp->StartTree(*EnemyAI->BehaviorTree);
	}
}

void AEnemyAIController::Attack()
{
	EnemyAI->SetCanAttack(true);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AEnemyAIController::AttackDelayEnd, EnemyAI->GetAttackDelay());
}

void AEnemyAIController::SetIsAlive(bool IsAlive)
{
	//Updates Blackboard value of AI IsAlive
	BlackboardComp->SetValueAsBool(BlackboardIsAliveKey, IsAlive);
}

void AEnemyAIController::AttackDelayEnd()
{
	auto GameInstance = Cast<UMainGameInstance>(GetGameInstance());
	if (GameInstance && EnemyAI->GetCanDoDamage())
	{
		GameInstance->SetDamageTaken(EnemyAI->GetAIDamage());
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);		
	}
	EnemyAI->SetCanAttack(false);
}