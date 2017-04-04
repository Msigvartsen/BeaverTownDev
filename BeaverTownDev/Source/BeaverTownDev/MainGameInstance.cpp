// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "MainGameInstance.h"

void UMainGameInstance::ResetStats()
{
	MaxHealth = 100.f;
	Health = MaxHealth;
	Minerals = 0;
	WoodenKey = false;
}


float UMainGameInstance::GetHealthPercent()
{
	return Health / MaxHealth;
}

void UMainGameInstance::SetMinerals(int32 PickedUpMinerals)
{
	Minerals += PickedUpMinerals;
	UE_LOG(LogTemp,Warning,TEXT("PICKED UP CRYSTALS TO GAME INSTANCE"))
}

void UMainGameInstance::SetDamageTaken(float Damage)
{
	Health -= Damage;
	if (Health <= 0.f)
	{
		GetWorld()->GetFirstPlayerController()->GetCharacter()->Destroy();
		ResetStats();
		UGameplayStatics::OpenLevel(this, FName("MainMenu"));
	}
	UE_LOG(LogTemp, Warning, TEXT("TOOK DAMAGE IN GAME INSTANCE"))
}

int32 UMainGameInstance::GetMinerals()
{
	return Minerals;
}

void UMainGameInstance::SetHealth(float inHealth)
{
	Health += inHealth;
}

bool UMainGameInstance::GetWoodenKey()
{
	return WoodenKey;
}

void UMainGameInstance::SetWoodenKey(bool KeyStatus)
{
	WoodenKey = KeyStatus;
}