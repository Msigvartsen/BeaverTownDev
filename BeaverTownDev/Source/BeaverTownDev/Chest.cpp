// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "Chest.h"

void AChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AActor* Character = Cast<AActor>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	if (Trigger && Character)
	{
		if (Trigger->IsOverlappingActor(Character))
		{
			OpenEvent();
		}
		else
		{
			CloseEvent();
		}
	}
}

void AChest::OpenEvent()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling derived class OpenEvent"))
	if (bIsOpenEvent == false)
	{
		bIsOpenEvent = true;
		AlexOpen.Broadcast();
	}
}

void AChest::CloseEvent()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling derived class CloseEvent"))
	if (bIsOpenEvent == true)
	{
		bIsOpenEvent = false;
		AlexClose.Broadcast();
	}
}


