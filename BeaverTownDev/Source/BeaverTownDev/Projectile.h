// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class BEAVERTOWNDEV_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	

	AProjectile();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


	void LaunchProjectile(float DeltaTime);

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
		UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult &SweepResult);
	

	UPROPERTY(EditAnywhere)
		USceneComponent* ProjectileRoot = nullptr;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ProjectileMesh = nullptr;
	UPROPERTY(EditAnywhere)
		UPrimitiveComponent* ProjectileCollision = nullptr;
	UPROPERTY(EditAnywhere)
		float ProjectileSpeed = 1000.f;
	UPROPERTY(EditAnywhere)
		float ProjectileDamage = 35.f;
	UPROPERTY(EditAnywhere)
		float DespawnTime = .7f;
};
