// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "MainCharacter.h"
#include "TorchPickup.h"


// Sets default values
ATorchPickup::ATorchPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATorchPickup::BeginPlay()
{
	Super::BeginPlay();
	CharRef = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());

}

// Called every frame
void ATorchPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsHeld)
	{
		SetActorLocation(CharRef->GetMesh()->GetSocketLocation(FName("hand_r")));
		SetActorRotation(FRotator(0.f, CharRef->GetActorRotation().Yaw - 45.f, 20.f));
	}
}

void ATorchPickup::Initialize(UStaticMeshComponent* MeshToSet)
{
	MeshRef = MeshToSet;
}
