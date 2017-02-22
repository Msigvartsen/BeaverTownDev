// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "Pickup.h"
#include "Chest.h"
#include "Lever.h"

void ALever::OpenEvent()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling Lever OpenEvent"))

	if (bIsOpenEvent == false)
	{
		bIsOpenEvent = true;
		LeverOpen.Broadcast();

		// spawn chest
		auto SpawnLocation = FVector(FMath::RandRange(-400.f, -600.f), FMath::RandRange(-200.f, -100.f), 125.f);
		Spawn = GetWorld()->SpawnActor<AChest>(SpawnBlueprint, SpawnLocation, FRotator::ZeroRotator);
	}
}

void ALever::CloseEvent()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling Lever CloseEvent"))
	if (bIsOpenEvent == true)
	{
		bIsOpenEvent = false;
		LeverClose.Broadcast();

		// destroy chest
		if (Spawn)
		{
			Spawn->Destroy();
		}
	}
}



