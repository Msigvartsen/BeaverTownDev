// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "PushableObject.h"
#include "MainCharacter.h"

// Sets default values
APushableObject::APushableObject()
{

	PrimaryActorTick.bCanEverTick = true;	

}

void APushableObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APushableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


