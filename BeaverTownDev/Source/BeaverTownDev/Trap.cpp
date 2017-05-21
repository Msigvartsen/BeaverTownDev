// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "Trap.h"
#include "MainCharacter.h"
// Sets default values
ATrap::ATrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ATrap::BeginPlay()
{
	Super::BeginPlay();
	TrapActive = true;
}

// Called every frame
void ATrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (TrapActive)
	{
		TrapTriggered();
	}
}

void ATrap::TrapTriggered()
{
	//Checks if there are a trigger volume connected
	if (TrapTrigger)
	{
		AMainCharacter* MainCharacter = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
		if (TrapTrigger->IsOverlappingActor(MainCharacter))
		{
			UE_LOG(LogTemp, Warning, TEXT("Trap triggered!"))
			AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ObjectToSpawn, GetActorLocation() + GetActorForwardVector() *100.f, GetActorRotation());
			SpawnedActor->SetLifeSpan(Lifetime);
			UGameplayStatics::PlaySound2D(GetWorld(), TriggerSound, 1.f, 1.f, 0.f);
			TrapActive = false;
		}
	}
	
}

