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

		//Starts BehaviorTree to specific character
		BehaviorComp->StartTree(*EnemyAI->BehaviorTree);
	}

}

void AEnemyAIController::Attack()
{
	
	auto GameInstance = Cast<UMainGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		
		if (EnemyAI->GetCanAttack())
		{
			GameInstance->SetDamageTaken(EnemyAI->GetAIDamage());
			UE_LOG(LogTemp, Warning, TEXT("AI Dealing damage"))
		}	
	}
}