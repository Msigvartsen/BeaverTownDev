// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "Chest.h"

AChest::AChest()
{
	bOnlyInteractFromAngle = true;
	MinOpenAngle -= 45.f;
	MaxOpenAngle += 45.f;
}

void AChest::OpenEvent()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling derived class OpenEvent"))
		if (!IsChestOpen)
		{
			if (bIsOpenEvent == false)
			{
				bIsOpenEvent = true;
				ChestOpen.Broadcast();
				IsChestOpen = true;
			}
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


