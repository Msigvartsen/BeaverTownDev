
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
	void Interact();
	void GetHitResultFromLineTrace(FHitResult &HitResult);
	void ShowInventory();
	void HideInventory();
	//Character Variables

	UPROPERTY(EditAnywhere)
		float DodgeSpeed = 2000.f;
	UPROPERTY(EditAnywhere)
		float InteractReach = 100.f;
	UPROPERTY(EditAnywhere)
		float MeleeRange = 75.f;
	float Stamina = 100.f;
	float MaxStamina = 100.f;
	float Health = 100.f;
	float MaxHealth = 100.f;
	float StaminaRegeneration = 10.f;
	float MeleeDamage = 50.f;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
		bool IsInventoryVisible = false;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AProjectile> ProjectileBlueprint;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AComplexProjectile> ComplexProjectileBlueprint;

	//Character Getters
	UFUNCTION(BlueprintCallable)
		float GetHealthPercent() const;
	UFUNCTION(BlueprintCallable)
		float GetStaminaPercent() const;

};
