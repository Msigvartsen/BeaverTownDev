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
	
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));

	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	
	Sight->SightRadius = 900.f;
	Sight->LoseSightRadius = 1200.f;
	Sight->PeripheralVisionAngleDegrees = 120.F;

	//Setting Sight sense to detect anything
	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = true;

	//Registering sight sense to Perception Component
	AIPerceptionComponent->ConfigureSense(*Sight);


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
		AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnPerceptionUpdated);
	}

}

void AEnemyAIController::OnPerceptionUpdated(TArray<AActor*> UpdatedActors)
{
	for (AActor* Actor : UpdatedActors)
	{
		if (Actor->IsA<AMainCharacter>() && !GetSeeingPawn())
		{
			BlackboardComp->SetValueAsObject(BlackboardPlayerKey, Actor);
			return;
		}
	}
	//If the player does not exist in UpdatedActors, Set key to nullptr
	BlackboardComp->SetValueAsObject(BlackboardPlayerKey, nullptr);
}

AActor* AEnemyAIController::GetSeeingPawn()
{
	UObject* object = BlackboardComp->GetValueAsObject(BlackboardPlayerKey);

	return object ? Cast<AActor>(object) : nullptr;
}

void AEnemyAIController::Attack()
{
	UE_LOG(LogTemp,Warning,TEXT("AI ATTACKING OWOW"))
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