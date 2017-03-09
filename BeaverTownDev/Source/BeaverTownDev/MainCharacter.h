
#pragma once

#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

// Forward declarations
class AComplexProjectile;

UCLASS()
class BEAVERTOWNDEV_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMainCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetCollectedMinerals();
	void SetIsInteractActive(bool Status);
	void SetHealth(float DamageTaken);

private:
	UPROPERTY(EditAnywhere)
		UCameraComponent* PlayerCamera = nullptr;
	UPROPERTY(EditAnywhere)
		USpringArmComponent* CameraBoom = nullptr;
	
	//Input Functions
	void MoveX(float value);
	void MoveY(float value);
	void Melee();
	void Dodge();
	void RotateToMousePosition(float DeltaTime);
	void Shoot();
	void Heal();
	void Interact();
	void InteractReleased();
	void WeaponOne();
	void WeaponTwo();
	void GetHitResultFromLineTrace(FHitResult &HitResult, float Reach);
	void ShowInventory();
	void HideInventory();
	void ThrowRock();
	void ThrowNut();

	//Character Variables

	UPROPERTY(EditAnywhere)
		float DodgeSpeed = 2000.f;
	UPROPERTY(EditAnywhere)
		float InteractReach = 100.f;
	UPROPERTY(EditAnywhere)
		float MeleeRange = 75.f;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
		int32 Ammo = 4;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
		int32 MaxAmmo = 50;
	int32 WeaponOfChoice = 1;
	float MaxStamina = 100.f;
	float Stamina = MaxStamina;
	float MaxHealth = 100.f;
	float Health = MaxHealth;
	float StaminaRegeneration = 10.f;
	float MeleeDamage = 50.f;
	float HealingPotion = 35.f;
		
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
		bool IsInventoryVisible = false;
	UPROPERTY(BlueprintReadOnly, Category = "CharacterStats", meta = (AllowPrivateAccess = true))
		int32 CollectedMinerals = 0;
	bool bIsInteractActive = false;

	UPROPERTY(EditAnywhere,Category = "Projectiles")
		TSubclassOf<class AProjectile> ProjectileBlueprint;
	UPROPERTY(EditAnywhere, Category = "Projectiles")
		TSubclassOf<class AComplexProjectile> ComplexProjectileBlueprint;

public:
	//Character Getters

	UFUNCTION(BlueprintCallable)
		float GetHealthPercent() const;
	UFUNCTION(BlueprintCallable)
		float GetStaminaPercent() const;
	UFUNCTION(BlueprintCallable)
		int GetCollectedMinerals() const;
	UFUNCTION(BlueprintCallable)
		bool GetIsInteractActive() const;

};
