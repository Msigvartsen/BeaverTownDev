// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "FellableTree.h"

AFellableTree::AFellableTree()
{
	bCanBeDamaged = true;
}

void AFellableTree::OpenEvent()
{
	// Takes damage
	Health -= 25;
	PlayChopSound();
	if (Health <= 0 && bCanFall)
	{
		bCanFall = false;
		// continues in blueprint
		TreeOpen.Broadcast();
	}
}


