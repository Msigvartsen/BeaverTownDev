// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "StoneDoor.h"


// Sets default values
AStoneDoor::AStoneDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStoneDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStoneDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

