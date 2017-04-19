// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "TorchStatic.h"


// Sets default values
ATorchStatic::ATorchStatic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATorchStatic::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATorchStatic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

