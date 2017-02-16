
#pragma once

#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

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

	//Character Variables

	UPROPERTY(EditAnywhere)
		float DodgeSpeed = 2000.f;
	float Stamina = 100.f;
	float MaxStamina = 100.f;
	float Health = 100.f;
	float MaxHealth = 100.f;
	float StaminaRegeneration = 3.f;

	//Character Getters
	UFUNCTION(BlueprintCallable)
		float GetHealthPercent();
	UFUNCTION(BlueprintCallable)
		float GetStaminaPercent();

};
