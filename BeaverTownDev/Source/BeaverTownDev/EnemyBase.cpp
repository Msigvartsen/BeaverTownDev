// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "MainCharacter.h"
#include "EnemyBase.h"


// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	if (!PlayerCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("Player not found"))
	}
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (LinetraceTowardPlayer())
	{
		MoveTowardPlayer();
	}
	else
	{
		Time += DeltaTime;
		if (Time < 1.f)
		{
			MoveForward();
		}
		else if (Time < 2.f)
		{
			MoveBackwards();
		}
		else if (Time < 3.f)
		{
			MoveLeft();
		}
		else if (Time < 4.f)
		{
			MoveRight();
		}
		else
		{
			Time = 0;
		}
	}
	if (Health <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy died"))
		Destroy();
	}
}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyBase::MoveForward()
{
	AddMovementInput(FVector::ForwardVector, .5f);
}

void AEnemyBase::MoveBackwards()
{
	AddMovementInput(FVector::ForwardVector, -.5f);
}

void AEnemyBase::MoveRight()
{
	AddMovementInput(FVector::RightVector, .5f);
}

void AEnemyBase::MoveLeft()
{
	AddMovementInput(FVector::RightVector, -.5f);
}

void AEnemyBase::Shoot()
{
	// TODO spawn projectile with player rotation
}

void AEnemyBase::MoveTowardPlayer()
{
	FVector PlayerDirection = GetVectorTowardPlayer();
	AddMovementInput(PlayerDirection.GetSafeNormal(), .5f);
}

bool AEnemyBase::LinetraceTowardPlayer()
{
	FHitResult HitResult;
	FVector StartTrace = GetActorLocation();
	FVector EndTrace = GetActorLocation() + (GetVectorTowardPlayer().GetSafeNormal() * AggroRange);

	DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor(0, 255, 0), false, 1.f, 0, 10.f);

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartTrace,
		EndTrace,
		ECollisionChannel::ECC_Visibility,
		FCollisionQueryParams(FName(""), false, this)
	))
	{
		if (HitResult.GetActor()->GetClass()->IsChildOf(AMainCharacter::StaticClass()))
		{
			return true;
		}
	}
	return false;
}

FVector AEnemyBase::GetVectorTowardPlayer()
{
	FVector PlayerLocation = PlayerCharacter->GetActorLocation();
	FVector EnemyLocation = GetActorLocation();
	return PlayerLocation - EnemyLocation;
}

void AEnemyBase::RemoveHealth(int32 Damage)
{
	Health -= Damage;
}
