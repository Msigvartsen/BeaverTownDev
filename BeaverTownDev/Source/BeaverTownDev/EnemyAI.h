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
	float Health = MaxHealth;
	UPROPERTY(EditAnywhere, Category = "AI")
		float AIDamage = 30.f;
	UPROPERTY(EditAnywhere, Category = "WaypointIndex")
		int32 WaypointIndex = 0;
	
	bool CanAttack = false;

	UPROPERTY(EditDefaultsOnly)
	USphereComponent* AttackRange = nullptr;

	class AMainCharacter* Player = nullptr;


public:
	//Getters
	UFUNCTION(BlueprintCallable,Category = "EnemyAI")
	float GetHealthPercent() const { return Health / MaxHealth; }
	
	UFUNCTION(BlueprintCallable,Category = "AI")
	void SetTakeDamage(float Damage) { Health -= Damage; }

	UFUNCTION()
	int32 GetWaypointIndex() const { return WaypointIndex; }

	UFUNCTION()
		float GetAIDamage() const { return AIDamage; }

	UFUNCTION()
		bool GetCanAttack() const { return CanAttack; }
};
