// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "Trap.h"
#include "Projectile.h"
#include "MainCharacter.h"
// Sets default values
ATrap::ATrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TrapRoot = CreateDefaultSubobject<USceneComponent>(TEXT("TrapRoot"));
	TrapMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TrapMesh"));
	RootComponent = TrapRoot;
	TrapMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATrap::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ATrap::TrapTriggered()
{
	if (!TrapTrigger) { return; }
	AMainCharacter* MainCharacter = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	if (TrapTrigger->IsOverlappingActor(MainCharacter))
	{	
		UE_LOG(LogTemp,Warning,TEXT("Trap triggered!"))
		GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, GetActorLocation() + GetActorForwardVector() *100.f, GetActorRotation());
	}
}

