// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "RollingDoor.generated.h"

class ATorchStatic;

UCLASS()
class BEAVERTOWNDEV_API ARollingDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARollingDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "RollingDoor")
		void OpenDoor();
	UFUNCTION(BlueprintImplementableEvent, Category = "RollingDoor")
		void CloseDoor();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		ATorchStatic* Torch1 = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		ATorchStatic* Torch2 = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		ATorchStatic* Torch3 = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		ATorchStatic* Torch4 = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		ATorchStatic* Torch5 = nullptr;

};
