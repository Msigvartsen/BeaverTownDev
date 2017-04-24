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
	if (bIsOpenEvent == false)
	{
		if (!bOpenOnce)
		{
			bIsOpenEvent = true;
		}
		ChestOpen.Broadcast();
	}
}

void AChest::CloseEvent()
{
	if (bIsOpenEvent == true)
	{
		bIsOpenEvent = false;
		ChestClose.Broadcast();
	}
}


