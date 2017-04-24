// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "EnemyAI.h"


AEnemyAI::AEnemyAI()
{
 
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemyAI::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Health < 0)
	{
		Destroy();
	}

}

void AEnemyAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyAI::AIAttack()
{
	UE_LOG(LogTemp,Warning,TEXT("AI ATTACKING"))

}
