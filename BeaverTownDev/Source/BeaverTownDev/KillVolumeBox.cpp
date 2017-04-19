// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "MainCharacter.h"
#include "KillVolumeBox.h"



AKillVolumeBox::AKillVolumeBox()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	Killbox = CreateDefaultSubobject<UBoxComponent>(TEXT("KillBox"));
	Killbox->OnComponentBeginOverlap.AddDynamic(this, &AKillVolumeBox::OnOverlapBegin);

}

// Called when the game starts or when spawned
void AKillVolumeBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKillVolumeBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKillVolumeBox::AKillVolumeBox::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{

	}
}