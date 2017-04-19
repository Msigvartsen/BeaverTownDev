// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "MainCharacter.h"
#include "ThrowableItems.h"


AThrowableItems::AThrowableItems()
{
 
	PrimaryActorTick.bCanEverTick = true;
}


void AThrowableItems::BeginPlay()
{
	Super::BeginPlay();
	
}


void AThrowableItems::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AThrowableItems::SetIsThrown(bool IsThrow)
{
	IsThrown = IsThrow;
}