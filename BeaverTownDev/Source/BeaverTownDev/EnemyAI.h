// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "EnemyAI.generated.h"

UCLASS()
class BEAVERTOWNDEV_API AEnemyAI : public ACharacter
{
	GENERATED_BODY()

public:
	
	AEnemyAI();

	virtual void Tick(float DeltaTime) override;


	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "AI")
	class UBehaviorTree* BehaviorTree;

protected:
	
	virtual void BeginPlay() override;


private:
	
	UPROPERTY(EditAnywhere,Category = "AI")
		float MaxHealth = 100.f;

	float Health;

	UPROPERTY(EditAnywhere, Category = "AI")
		float AIDamage = 30.f;
	//Despawn timer after death
	UPROPERTY(EditAnywhere, Category = "AI")
		float DespawnTimer = 3.f;
	UPROPERTY(EditAnywhere, Category = "AI")
		float PatrolSpeed = 150.f;
	UPROPERTY(EditAnywhere, Category = "AI")
		float ChaseSpeed = 400.f;
	UPROPERTY(EditAnywhere, Category = "AI")
		float AggroRange = 1000.f;
	UPROPERTY(EditAnywhere, Category = "WaypointIndex")
		int32 WaypointIndex = 0;
	UPROPERTY(EditANywhere, Category = "AI")
		float AttackDelay = .7f;

	
	FTimerHandle TimerHandle;
	bool IsAlive = true;
	bool CanAttack = false;
	bool IsAggro = false;
	bool CanDoDamage = false;

	UPROPERTY(EditDefaultsOnly)
	USphereComponent* AttackRange = nullptr;

	class AEnemyAIController* AIController = nullptr;

	class AMainCharacter* Player = nullptr;

	UPROPERTY(EditAnywhere)
		USoundBase* HurtSound;

	void LineTraceToPlayer();
	FVector GetVectorTowardPlayer();
	void Despawn();

public:

	//Getters // Setters

	UFUNCTION(BlueprintCallable,Category = "EnemyAI")
		bool GetIsAlive() const { return IsAlive; }
	UFUNCTION(BlueprintCallable,Category = "EnemyAI")
	float GetHealthPercent() const { return Health / MaxHealth; }
	
	UFUNCTION(BlueprintCallable, Category = "EnemyAI")
		float GetHealth() const { return Health; }

	UFUNCTION(BlueprintCallable, Category = "AI")
		void SetTakeDamage(float Damage);

	UFUNCTION()
	int32 GetWaypointIndex() const { return WaypointIndex; }

	UFUNCTION()
		float GetAIDamage() const { return AIDamage; }

	UFUNCTION(BlueprintCallable)
		bool GetCanAttack() const { return CanAttack; }

	UFUNCTION(BlueprintCallable)
		bool GetIsAggro() const { return IsAggro; }

	UFUNCTION(BlueprintCallable)
		void SetCanAttack(bool Attacking) { CanAttack = Attacking; }

	UFUNCTION()
		bool GetCanDoDamage() { return CanDoDamage; }
	UFUNCTION()
		float GetAttackDelay() { return AttackDelay; }
};
