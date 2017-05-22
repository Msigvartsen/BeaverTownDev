// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "MainCharacter.h"
#include "MainGameInstance.h"



void UMainGameInstance::ResetStats()
{
	MaxHealth = 100.f;
	Health = MaxHealth;
	WoodenKey = false;
}

float UMainGameInstance::GetHealthPercent()
{
	return Health / MaxHealth;
}



void UMainGameInstance::SetDamageTaken(float Damage)
{
	AMainCharacter* PC = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	HurtSound = PC->GetHurtSound();
	Health -= Damage;
	if (CanPlaySound)
	{
		CanPlaySound = false;
		UGameplayStatics::PlaySound2D(GetWorld(), HurtSound, 5.f, 1.f, 0.f);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UMainGameInstance::ResetCanPlaySound, SoundDelay, false);
	}
	if (Health <= 0.f)
	{
		PC->SetIsPlayerAlive(false);
		LoadRestartGameUI();
	}
}



void UMainGameInstance::SetHealthIncrease(float inHealth)
{
	Health += inHealth;
	if (Health >= MaxHealth)
	{
		Health = MaxHealth;
	}
}

void UMainGameInstance::ResetHealth(float inHealth)
{
	Health = inHealth;
}

bool UMainGameInstance::GetWoodenKey()
{
	return WoodenKey;
}

void UMainGameInstance::SetWoodenKey(bool KeyStatus)
{
	WoodenKey = KeyStatus;
}

void UMainGameInstance::ResetCanPlaySound()
{
	CanPlaySound = true;
}