
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

	void SetIsInteractActive(bool Status);

private:
	UPROPERTY(EditAnywhere)
		UCameraComponent* PlayerCamera = nullptr;
	UPROPERTY(EditAnywhere)
		USpringArmComponent* CameraBoom = nullptr;
	
	//Input Functions
	void MoveX(float value);
	void MoveY(float value);
	void Melee();
	void JumpPressed();
	void JumpReleased();
	void RotateToMousePosition(float DeltaTime);
	void Interact();
	void InteractReleased();
	void GetHitResultFromLineTrace(FHitResult &HitResult, float Reach);
	virtual void Landed(const FHitResult & Hit) override;
	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode) override;

	//Character Variables

	UPROPERTY(EditAnywhere,Category="CharacterStats")
		float DodgeSpeed = 2000.f;
	UPROPERTY(EditAnywhere, Category = "CharacterStats")
		float InteractReach = 100.f;
	UPROPERTY(EditAnywhere, Category = "CharacterStats")
		float MeleeRange = 75.f;
	UPROPERTY(EditAnywhere, Category = "CharacterStats")
		float MeleeDamage = 50.f;

	float StartJumpTime = 0;
	float EndJumpTime = 0;
	bool bCanJump;	
	bool bIsInteractActive = false;

	UPROPERTY(EditAnywhere,Category = "Projectiles")
		TSubclassOf<class AProjectile> ProjectileBlueprint;
	UPROPERTY(EditAnywhere, Category = "Projectiles")
		TSubclassOf<class AComplexProjectile> ComplexProjectileBlueprint;

public:
	//Character Getters

	UFUNCTION(BlueprintCallable)
		bool GetIsInteractActive() const;

};
