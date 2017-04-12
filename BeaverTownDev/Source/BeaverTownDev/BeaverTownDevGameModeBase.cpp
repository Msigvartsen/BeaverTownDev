// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "Raft.h"
#include "BeaverTownDevGameModeBase.h"

void ABeaverTownDevGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::PlaySound2D(GetWorld(), Music, 1.f, 1.f, 0.f);
}

void ABeaverTownDevGameModeBase::SetRaft(ARaft* RaftToSet)
{
	Raft = RaftToSet;
}

ARaft* ABeaverTownDevGameModeBase::GetRaft()
{
	return Raft;
}



