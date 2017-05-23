// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "Crate.h"

ACrate::ACrate()
{
	// Sets variables declared in base class
	bOnlyInteractFromAngle = false;
	bCanBeDamaged = true;
}

void ACrate::OpenEvent()
{
	// Takes damage
	Health -= 70;
	if (Health <= 0)
	{
		bIsBroken = true;
		RandomSpawn = FMath::RandRange(0, 2);
		if (DestroyParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticle, GetTransform(), true);
		}
	}
	// continues in blueprint
	CrateOpen.Broadcast();
}

bool ACrate::GetIsBroken()
{
	return bIsBroken;
}
