// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "BurnableObjects.h"


// Sets default values
ABurnableObjects::ABurnableObjects()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABurnableObjects::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABurnableObjects::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

