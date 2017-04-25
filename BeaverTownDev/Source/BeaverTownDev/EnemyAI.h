// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "EnemyAI.generated.h"

UCLASS()
class BEAVERTOWNDEV_API AEnemyAI : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyAI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "AI")
	class UBehaviorTree* BehaviorTree;

private:
	
	float MaxHealth = 100.f;
	float Health = MaxHealth;
	
	UPROPERTY(EditAnywhere, Category = "WaypointIndex")
		int32 WaypointIndex = 0;
	

protected:
	UFUNCTION(BlueprintCallable, Category = "AI")
		void AIAttack();

public:
	//Getters
	UFUNCTION(BlueprintCallable,Category = "EnemyAI")
	float GetHealthPercent() const { return Health / MaxHealth; }
	
	UFUNCTION(BlueprintCallable,Category = "AI")
	void SetTakeDamage(float Damage) { Health -= Damage; }

	UFUNCTION()
	int32 GetWaypointIndex() const { return WaypointIndex; }

};
