// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "EnemyAI.h"
#include "ThrowableRock.h"

AThrowableRock::AThrowableRock()
{
	
}

void AThrowableRock::BeginPlay()
{
	Super::BeginPlay();

	RockMesh = FindComponentByClass<UStaticMeshComponent>();
	RockMesh->OnComponentHit.AddDynamic(this, &AThrowableRock::OnHit);	
}

void AThrowableRock::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	
	if (GetIsThrown())
	{
		if (OtherActor->GetClass()->IsChildOf(AEnemyAI::StaticClass()))
		{
			AEnemyAI* EnemyRef = Cast<AEnemyAI>(OtherActor);
			EnemyRef->SetTakeDamage(RockDamage);
			SetIsThrown(false);
		}

	}
	
}
