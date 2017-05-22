// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"

/*
Component added to AMainCharacter.
Gives the player the ability to grab, throw and release objects
*/

// Forward declarations
class AThrowableItems;
class APushableObject;
class ATorchPickup;
class AThrowableRock;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BEAVERTOWNDEV_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGrabber();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

private:
	// Returns hit result from character linetrace
	FHitResult LineTraceFromCharacter();

	// Pointers to grabbable objects
	UPrimitiveComponent* ComponentToGrab = nullptr;
	AThrowableItems *ItemToThrow = nullptr;
	APushableObject* ObjectToPush = nullptr;
	ATorchPickup* TorchToHold = nullptr;
	FTimerHandle TimerHandle;
	AThrowableRock* Rock = nullptr;

	// Settings variables
	bool StartThrow = false;
	float DefaultThrowForce = 2000;
	UPROPERTY(EditAnywhere)
	float RockCollisionTimer = 3.f;
	float Reach = 20.f;
	bool IsHeld = false;

	UInputComponent* InputComponent = nullptr;
	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	void Grab();
	void Release();
	void Throw();
	void FindPhysicsHandle();
	void FindInputComponent();
	void RockCollisionTimerEnd();
};
