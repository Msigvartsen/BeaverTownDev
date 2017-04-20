// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "MainGameInstance.h"
#include "DamageVolume.h"


// Sets default values
ADamageVolume::ADamageVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	RootComponent = Root;
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	Box->SetupAttachment(RootComponent);
	Box->bGenerateOverlapEvents = true;

}

// Called when the game starts or when spawned
void ADamageVolume::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<UMainGameInstance>(GetWorld()->GetGameInstance());
	
}

// Called every frame
void ADamageVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Box->IsOverlappingActor(Cast<AActor>(GetWorld()->GetFirstPlayerController()->GetCharacter())))
	{
		UE_LOG(LogTemp, Warning, TEXT("OVERLAPPING"))

			if (bPeriodicDamage)
			{
				GameInstance->SetDamageTaken(DPS * DeltaTime);
			}
			else
			{
				GameInstance->SetDamageTaken(SingleDamage);
			}
	}
}
