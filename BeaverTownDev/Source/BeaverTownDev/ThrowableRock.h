// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ThrowableItems.h"
#include "ThrowableRock.generated.h"

/**
 * 
 */
UCLASS()
class BEAVERTOWNDEV_API AThrowableRock : public AThrowableItems
{
	GENERATED_BODY()
	
private:
	
	
	virtual void BeginPlay() override;

	bool IsThrown = false;
	

public:
	AThrowableRock();
	
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditDefaultsOnly, Category = "Hitbox")
		UStaticMeshComponent* RockMesh = nullptr;
};
