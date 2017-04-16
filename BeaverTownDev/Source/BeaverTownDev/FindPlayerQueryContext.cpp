// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "MainCharacter.h"
#include "EnemyAIController.h"
#include "FindPlayerQueryContext.h"

void UFindPlayerQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);

	AEnemyAIController* AIController = Cast<AEnemyAIController>((Cast<AActor>((QueryInstance.Owner).Get())->GetInstigatorController()));

	if (AIController && AIController->GetSeeingPawn())
	{
		AIController->GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = 200.f;
		UEnvQueryItemType_Actor::SetContextHelper(ContextData, AIController->GetSeeingPawn());
	}
}



