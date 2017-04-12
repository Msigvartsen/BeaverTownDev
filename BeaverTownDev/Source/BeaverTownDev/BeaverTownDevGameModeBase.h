// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "BeaverTownDevGameModeBase.generated.h"

class ARaft;

UCLASS()
class BEAVERTOWNDEV_API ABeaverTownDevGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
private:
	ARaft* Raft = nullptr;

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		USoundBase* Music = nullptr;
public:
	void SetRaft(ARaft* RaftToSet);
	UFUNCTION(BlueprintCallable, Category = Getter)
	ARaft* GetRaft();

};
