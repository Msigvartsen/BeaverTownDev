// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "MainCharacter.h"
#include "ThrowableItems.h"


AThrowableItems::AThrowableItems()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AThrowableItems::SetIsThrown(bool IsThrow)
{
	IsThrown = IsThrow;
}