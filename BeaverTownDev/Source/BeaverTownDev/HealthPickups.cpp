// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "HealthPickups.h"

AHealthPickups::AHealthPickups()
{

}

void AHealthPickups::BeginPlay()
{
	Super::BeginPlay();

}

float AHealthPickups::HealTarget()
{
	return HealingApplied;
}


