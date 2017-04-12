// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "MainGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BEAVERTOWNDEV_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()
private:

	//Player stats
	UPROPERTY(EditAnywhere, Category = "PlayerStats")
		float MaxHealth = 100.f;
	UPROPERTY(EditAnywhere,Category = "PlayerStats")
		float Health = MaxHealth;
	UPROPERTY(EditAnywhere, Category = "PlayerStats")
		float Minerals = 0;
	UPROPERTY(EditAnywhere)
		USoundBase* HurtSound;
	bool WoodenKey = false;

	UPROPERTY(EditAnywhere)
		USoundBase* Music;

public:

	void ResetStats();

	//Player Function getter/setters

	UFUNCTION(BlueprintCallable,Category = "PlayerStats")
		float GetHealthPercent();

	UFUNCTION(BlueprintCallable, Category = "PlayerStats")
		void SetDamageTaken(float Damage);

	UFUNCTION(BlueprintCallable, Category = "PlayerStats")
		void SetMinerals(int32 PickedUpMinerals);

	UFUNCTION(BlueprintCallable, Category = "PlayerStats")
		int32 GetMinerals();

	UFUNCTION(BlueprintCallable,Category = "PlayerStats")
		void SetHealth(float inHealth);
	
	UFUNCTION(BlueprintCallable, Category = "PlayerStats")
		bool GetWoodenKey();

	UFUNCTION(BlueprintCallable,Category = "PlayerStats")
	void SetWoodenKey(bool KeyStatus);
};
