// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "KillVolumeBox.generated.h"

UCLASS()
class BEAVERTOWNDEV_API AKillVolumeBox : public AActor
{
	GENERATED_BODY()
	

private:
	UBoxComponent* Killbox = nullptr;

	void AKillVolumeBox::OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:

	virtual void BeginPlay() override;

public:	
	AKillVolumeBox();
	virtual void Tick(float DeltaTime) override;

	
	
};
