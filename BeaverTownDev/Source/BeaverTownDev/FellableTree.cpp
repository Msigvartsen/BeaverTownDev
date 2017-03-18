// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "FellableTree.h"

AFellableTree::AFellableTree()
{
	bCanBeDamaged = true;
}

void AFellableTree::OpenEvent()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling Tree OpenEvent"))

	// Takes damage
	Health -= 25;
	if (Health <= 0)
	{
		// continues in blueprint
		TreeOpen.Broadcast();
	}
}


