// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "Raft.h"
#include "RollingDoor.h"
#include "BeaverTownDevGameModeBase.h"

void ABeaverTownDevGameModeBase::SetRaft(ARaft* RaftToSet)
{
	Raft = RaftToSet;
}

void ABeaverTownDevGameModeBase::SetDoor(ARollingDoor* DoorToSet)
{
	Door = DoorToSet;
}

ARaft* ABeaverTownDevGameModeBase::GetRaft()
{
	return Raft;
}

ARollingDoor* ABeaverTownDevGameModeBase::GetDoor()
{
	return Door;
}



