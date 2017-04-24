// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "DestructibleRock.h"

ADestructibleRock::ADestructibleRock()
{
	bCanBeDamaged = true;
}

void ADestructibleRock::OpenEvent()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling Rock OpenEvent"))

	// Takes damage
	Health -= Damage;
	PlayRockHitSound();
	if (Health <= 0)
	{
		// continues in blueprint
		BreakRock();
	}
}



