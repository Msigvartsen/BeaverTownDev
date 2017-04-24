// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "MainGameInstance.h"
#include "MainCharacter.h"
#include "Chest.h"

AChest::AChest()
{
	bOnlyInteractFromAngle = true;
	MinOpenAngle -= 45.f;
	MaxOpenAngle += 45.f;
}

void AChest::OpenEvent()
{
	if (bIsOpenEvent == false && CanBeOpened)
	{
		if (!bOpenOnce)
		{
			bIsOpenEvent = true;
		}
		ChestOpen.Broadcast();
		if (LootTexts.ToString() == TEXT("WoodenKey"))
		{
			UMainGameInstance* GameInstance = Cast<UMainGameInstance>(GetWorld()->GetGameInstance());
			GameInstance->SetWoodenKey(true);
		}
		if (LootTexts.ToString() == TEXT("WoodPart"))
		{
			UMainGameInstance* GameInstance = Cast<UMainGameInstance>(GetWorld()->GetGameInstance());
			Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter())->SetOverheadText();
			GameInstance->SetWoodParts();
			UE_LOG(LogTemp,Warning,TEXT("WoodParts::: %d"), GameInstance->GetWoodParts())
		}
		CanBeOpened = false;
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


