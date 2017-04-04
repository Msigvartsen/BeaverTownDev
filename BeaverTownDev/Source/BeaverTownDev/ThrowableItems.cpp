// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "MainCharacter.h"
#include "ThrowableItems.h"


// Sets default values
AThrowableItems::AThrowableItems()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AThrowableItems::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AThrowableItems::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}