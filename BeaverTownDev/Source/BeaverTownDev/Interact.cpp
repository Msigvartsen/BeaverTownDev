// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "Interact.h"

// Sets default values
AInteract::AInteract()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // Tick is DISABLED.

	MainRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Main Root"));
	RootComponent = MainRoot;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AInteract::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteract::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteract::OpenEvent()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling base class OpenEvent"))
}

void AInteract::CloseEvent()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling base class CloseEvent"))
}

bool AInteract::GetIsOpenEvent()
{
	return bIsOpenEvent;
}

bool AInteract::GetOnlyInteractFromAngle()
{
	return bOnlyInteractFromAngle;
}

float AInteract::GetMaxOpenAngle()
{
	return MaxOpenAngle;
}

float AInteract::GetMinOpenAngle()
{
	return MinOpenAngle;
}

bool AInteract::GetCanBeDamaged()
{
	return bCanBeDamaged;
}
