// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "MainCharacter.h"
#include "MainGameInstance.h"
#include "EnemyAI.h"


AEnemyAI::AEnemyAI()
{
	PrimaryActorTick.bCanEverTick = true;
	AttackRange = CreateDefaultSubobject<USphereComponent>(TEXT("AttackRange"));
	AttackRange->SetupAttachment(GetRootComponent());
}

void AEnemyAI::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
	Player = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
}

// Called every frame
void AEnemyAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	LineTraceToPlayer();

	if (AttackRange->IsOverlappingActor(Player))
	{
		CanAttack = true;
		UE_LOG(LogTemp,Warning,TEXT("Can attack"))
	}
	else
	{
		CanAttack = false;
		UE_LOG(LogTemp, Warning, TEXT("Cannot attack"))
	}

	if (Health <= 0)
	{	
		IsAlive = false;
		Destroy();
	}
	
}

void AEnemyAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyAI::SetTakeDamage(float Damage)
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), HurtSound,GetActorLocation(),1.f,1.f,0.f);
	Health -= Damage;
}

void AEnemyAI::LineTraceToPlayer()
{
	UE_LOG(LogTemp,Warning,TEXT("LineTracing!"))
	FHitResult HitResult;
	FVector StartTrace = GetActorLocation();
	FVector EndTrace = GetActorLocation() + (GetVectorTowardPlayer().GetSafeNormal() * 1000.f);

	DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor(0, 0, 255),true, .1f, 0, 10.f);

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartTrace,
		EndTrace,
		ECollisionChannel::ECC_Visibility,
		FCollisionQueryParams(FName(""), false, this)
		))
	{
		if (HitResult.GetActor()->IsA(AMainCharacter::StaticClass()))
		{
			IsAggro = true;
		}
		else
		{
			IsAggro = false;
		}
	}
}

FVector AEnemyAI::GetVectorTowardPlayer()
{
	FVector PlayerLocation = Player->GetActorLocation();
	FVector EnemyLocation = GetActorLocation();
	return PlayerLocation - EnemyLocation;
}