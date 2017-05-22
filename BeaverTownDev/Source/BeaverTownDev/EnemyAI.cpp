// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "MainCharacter.h"
#include "MainGameInstance.h"
#include "EnemyAIController.h"
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
	AIController = Cast<AEnemyAIController>(this->GetController());
	AIController->SetIsAlive(IsAlive);
	GetCharacterMovement()->MaxWalkSpeed = PatrolSpeed;
}

// Called every frame
void AEnemyAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	LineTraceToPlayer();

	//If AI is alive and player is withing attacking range
	if (AttackRange->IsOverlappingActor(Player) && IsAlive)
	{
		CanDoDamage = true;
	}
	else
	{
		CanDoDamage = false;
	}

	//When AI health is below 0, death animation is played, and starts a despawn timer for the character 
	if (Health <= 0 && IsAlive)
	{	
		IsAlive = false;
		AIController->SetIsAlive(IsAlive);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AEnemyAI::Despawn, DespawnTimer);
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
	
	FHitResult HitResult;
	FVector StartTrace = GetActorLocation();
	FVector EndTrace = GetActorLocation() + (GetVectorTowardPlayer().GetSafeNormal() * AggroRange);


	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartTrace,
		EndTrace,
		ECollisionChannel::ECC_Visibility,
		FCollisionQueryParams(FName(""), false, this)
		))
	{
		//If AI spots the character, start chase mode. (Gives AI faster movement)
		if (HitResult.GetActor()->IsA(AMainCharacter::StaticClass()))
		{
			IsAggro = true;
			GetCharacterMovement()->MaxWalkSpeed = ChaseSpeed;
		}
		//If AI havent seen the player, sets walking speed to slow
		else
		{
			IsAggro = false;
			GetCharacterMovement()->MaxWalkSpeed = PatrolSpeed;
		}
	}
}

FVector AEnemyAI::GetVectorTowardPlayer()
{
	FVector PlayerLocation = Player->GetActorLocation();
	FVector EnemyLocation = GetActorLocation();
	return PlayerLocation - EnemyLocation;
}

void AEnemyAI::Despawn()
{
	if (GetWorld())
	{
		Destroy();
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);	
	}
}