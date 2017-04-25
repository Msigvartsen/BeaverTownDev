// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "FloatingCrate.h"
#include "StreamCollision.h"


// Sets default values
AStreamCollision::AStreamCollision()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StreamCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Lord Of Dragmar"));
	StreamCollision->SetupAttachment(RootComponent);
	StreamCollision->bGenerateOverlapEvents = true;

	StreamArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ARROW"));
	StreamArrow->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AStreamCollision::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStreamCollision::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<AActor*>OverlappingActors;
	StreamCollision->GetOverlappingActors(OverlappingActors);
	for (auto* Actor : OverlappingActors)
	{
		if (Actor->GetClass()->IsChildOf(AFloatingCrate::StaticClass()))
		{
			Crate = Cast<AFloatingCrate>(Actor);
			Crate->MoveCrate(GetActorForwardVector());
			if (bMakeFall)
			{
				Crate->MakeFall();
			}
			if (bStopFall)
			{
				Crate->StopFall();
			}
		}
	}
	

}

