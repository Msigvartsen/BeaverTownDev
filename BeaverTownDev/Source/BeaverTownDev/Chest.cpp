// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "Chest.h"

void AChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AActor* MyActor = Cast<AActor>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	if (Trigger->IsOverlappingActor(MyActor))
	{
		OpenEvent();
	}
	else
	{
		CloseEvent();
	}
}

void AChest::OpenEvent()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling derived class OpenEvent"))
	AlexOpen.Broadcast();
}

void AChest::CloseEvent()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling derived class CloseEvent"))
	AlexClose.Broadcast();

}


