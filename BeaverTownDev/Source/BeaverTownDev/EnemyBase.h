// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

class AMainCharacter;
class AComplexProjectile;

UCLASS()
class BEAVERTOWNDEV_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void MoveForward();
	void MoveBackwards();
	void MoveRight();
	void MoveLeft();
	void MoveTowardPlayer();
	void Attack();
	bool LinetraceTowardPlayer();
	FVector GetVectorTowardPlayer();
	void RemoveHealth(int32 Damage);
	
	UFUNCTION(BlueprintCallable,Category="EnemyHealth")
	float GetHealthPercent() const;

protected:
	AMainCharacter* PlayerCharacter = nullptr;
	float Time;
	float TimeInterval = 0.5f;
	UPROPERTY(EditAnywhere)
		float AggroRange = 500.f;
	float MaxHealth = 100.f;
	float Health = MaxHealth;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AComplexProjectile> ComplexProjectileBlueprint;
};