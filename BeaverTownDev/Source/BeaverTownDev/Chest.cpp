// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "Chest.h"


void AChest::OpenEvent()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling derived class OpenEvent"))
	if (bIsOpenEvent == false)
	{
		bIsOpenEvent = true;
		ChestOpen.Broadcast();
	}
}

void AChest::CloseEvent()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling derived class CloseEvent"))
	if (bIsOpenEvent == true)
	{
		bIsOpenEvent = false;
		ChestClose.Broadcast();
	}
}


