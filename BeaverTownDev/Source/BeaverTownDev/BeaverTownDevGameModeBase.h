// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "BeaverTownDevGameModeBase.generated.h"

class ARaft;
class ARollingDoor;

UCLASS()
class BEAVERTOWNDEV_API ABeaverTownDevGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
private:
	ARaft* Raft = nullptr;
	ARollingDoor* Door = nullptr;


	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		USoundBase* Music = nullptr;
public:
	void SetRaft(ARaft* RaftToSet);
	void SetDoor(ARollingDoor* DoorToSet);
	UFUNCTION(BlueprintCallable, Category = Getter)
		ARollingDoor* GetDoor();
	UFUNCTION(BlueprintCallable, Category = Getter)
		ARaft* GetRaft();

};
