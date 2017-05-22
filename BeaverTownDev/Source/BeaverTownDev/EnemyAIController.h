// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class BEAVERTOWNDEV_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
private:

	//BehaviorTree ref
	class UBehaviorTreeComponent* BehaviorComp;

	//Blackboard ref
	UBlackboardComponent* BlackboardComp;
	
	/*UPROPERTY(VisibleAnywhere)
	UAIPerceptionComponent* AIPerceptionComponent;*/

	//Blackboard Keys
	const FName BlackboardPlayerKey = FName("Player");
	const FName BlackboardIsAliveKey = FName("AIAlive?");
	const FName BlackboardIsAggroKey = FName("AIAggro?");
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName LocationToGoKey;
	
	class AEnemyAI* EnemyAI = nullptr;
	TArray<AActor*> BotTargetPoints;
	FTimerHandle TimerHandle;
	float AttackDelay = .7f;
	bool CanAttack = true;
	void AttackDelayEnd();
	virtual void Possess(APawn* Pawn) override;

public:

	AEnemyAIController();

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
	FORCEINLINE TArray<AActor*> GetAvailableTargetPoints() const { return BotTargetPoints; }

	UFUNCTION()
		void Attack();
	UFUNCTION()
		void SetIsAlive(bool IsAlive);
	UFUNCTION()
		void SetIsAggro(bool Aggro);
};
