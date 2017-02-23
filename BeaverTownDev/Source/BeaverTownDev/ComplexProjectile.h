// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ComplexProjectile.generated.h"

UCLASS()
class BEAVERTOWNDEV_API AComplexProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AComplexProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Shoot(float Speed);
	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

private:
	UPROPERTY(EditAnywhere)
		float LaunchSpeed = 1000.f;

	UPROPERTY(EditAnywhere)
		UProjectileMovementComponent* ProjectileMovement = nullptr;
	UPROPERTY(EditAnywhere)
		USceneComponent* ComplexProjectileRoot = nullptr;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ComplexProjectileMesh = nullptr;
	UPROPERTY(EditAnywhere)
		UShapeComponent* ComplexProjectileCollision = nullptr;


};
