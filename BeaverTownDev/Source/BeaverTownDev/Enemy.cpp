// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "Enemy.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EnemyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Enemy Root"));
	EnemyCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Enemy Collision"));
	EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyMesh"));
	RootComponent = EnemyRoot;
	EnemyMesh->SetupAttachment(RootComponent);
	EnemyCollision->SetupAttachment(RootComponent);
	EnemyCollision->bGenerateOverlapEvents = true;
	
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	MoveDirection = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - GetActorLocation();
	MoveDirection.Normalize();
	SetActorRotation(MoveDirection.Rotation());

}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	NewLocation += (MoveDirection * 100.f * DeltaTime);
	SetActorLocation(NewLocation);

	CurrentTurnDelay -= DeltaTime;
	///Turns the enemy after some time:
	if (CurrentTurnDelay < 0.f)
	{
		MoveDirection = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - GetActorLocation();
		MoveDirection.Normalize();
		SetActorRotation(MoveDirection.Rotation());

		CurrentTurnDelay = FMath::FRandRange(0.f, 1.f);
	}


	if (Health <= 0)
	{
		this->Destroy();
	}
}

float AEnemy::GetHealthPercent() const
{
	return Health / MaxHealth;
}

void AEnemy::SetDamageTaken(float DamageTaken)
{
	Health -= DamageTaken;
}
