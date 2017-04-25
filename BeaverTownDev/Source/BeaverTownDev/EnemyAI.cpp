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
	Player = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
}

// Called every frame
void AEnemyAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AttackRange->IsOverlappingActor(Player))
	{
		CanAttack = true;
	}
	else
	{
		CanAttack = false;
	}

	if (Health <= 0)
	{	
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

