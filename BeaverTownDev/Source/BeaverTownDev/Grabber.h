// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


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

	float Reach = 100.f;

	UInputComponent* InputComponent = nullptr;
	class UPhysicsHandleComponent* PhysicsHandle = nullptr;

	void Grab();
	void Release();
	void FindPhysicsHandle();
	void FindInputComponent();
};
