// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "Crate.h"

ACrate::ACrate()
{
	bOnlyInteractFromAngle = false;
	bCanBeDamaged = true;
}

void ACrate::OpenEvent()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling Crate OpenEvent"))



	// Takes damage
	Health -= 25;
	if (Health <= 0)
	{
		bIsBroken = true;
		RandomSpawn = FMath::RandRange(0, 2);
		UE_LOG(LogTemp, Warning, TEXT("RandSpawn: %d"), RandomSpawn)
	}

	// continues in blueprint
	CrateOpen.Broadcast();

}

bool ACrate::GetIsBroken()
{
	return bIsBroken;
}
