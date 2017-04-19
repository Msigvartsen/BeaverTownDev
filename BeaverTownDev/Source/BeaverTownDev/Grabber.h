// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"

class AThrowableItems;
class APushableObject;
class ATorchPickup;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BEAVERTOWNDEV_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGrabber();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	virtual void BeginPlay() override;

public:	


private:
	FHitResult LineTraceFromCharacter();
	UPrimitiveComponent* ComponentToGrab = nullptr;
	AThrowableItems *ItemToThrow = nullptr;
	APushableObject* ObjectToPush = nullptr;
	ATorchPickup* TorchToHold = nullptr;

	bool StartThrow = false;
	float DefaultThrowForce = 2000;
	float Reach = 20.f;
	bool IsHeld = false;
	UInputComponent* InputComponent = nullptr;
	class UPhysicsHandleComponent* PhysicsHandle = nullptr;

	void Grab();
	void Release();
	void Throw();
	void FindPhysicsHandle();
	void FindInputComponent();
};
