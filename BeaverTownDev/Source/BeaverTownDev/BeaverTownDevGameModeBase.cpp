// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "Raft.h"
#include "BeaverTownDevGameModeBase.h"

void ABeaverTownDevGameModeBase::SetRaft(ARaft* RaftToSet)
{
	Raft = RaftToSet;
}

ARaft* ABeaverTownDevGameModeBase::GetRaft()
{
	return Raft;
}



