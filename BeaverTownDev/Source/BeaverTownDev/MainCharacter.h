
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
	void FallingDamage();
	void RotateToMousePosition(float DeltaTime);
	void Interact();
	void InteractReleased();
	void GetHitResultFromLineTrace(FHitResult &HitResult, float Reach);
	virtual void Landed(const FHitResult & Hit) override;
	void SetTextRotation(UTextRenderComponent* TextRenderComp);
	void SetVisibilityOverheadText();
	void TimerEnd();
	void MeleeDelayEnd();
	//Character Variables

	
	UPROPERTY(EditAnywhere, Category = "CharacterStats")
		float InteractReach = 100.f;
	UPROPERTY(EditAnywhere, Category = "CharacterStats")
		float MeleeRange = 75.f;
	UPROPERTY(EditAnywhere, Category = "CharacterStats")
		float MeleeDamage = 50.f;
	UPROPERTY(EditAnywhere, Category = "CharacterStats")
		float OverheadTextDespawnTime = 2.f;

	FTimerHandle TimerHandle;
	FTimerHandle MeleeTimerHandle;

	float StartJumpTime = 0;
	float EndJumpTime = 0;
	bool bCanJump;	
	bool bIsInteractActive = false;
	bool IsPushingObject = false;
	bool bFalling = false;
	bool bCanTakeFallingDamage = false;
	float TurnInterpolationSpeed = 1000.f;
	bool IsTextVisible = false;
	bool CanMelee = true;
	FText LootText;
	
	UPROPERTY(EditAnywhere)
		float WalkSpeed = 400.f;

	class AChest* ChestRef = nullptr;

	UPROPERTY(EditAnywhere, Category = "Sound")
		USoundBase* HurtSound;
	UPROPERTY(EditAnywhere, Category = "TextRender")
		UTextRenderComponent* OverheadText;
public:
	//Character Getters

	UFUNCTION(BlueprintCallable)
		bool GetIsInteractActive() const;
	void SetIsPushingObject(bool IsPushing);
	void SetMaxWalkSpeed(float MovementSpeed);
	void SetOverheadText();
	USoundBase* GetHurtSound();

};
