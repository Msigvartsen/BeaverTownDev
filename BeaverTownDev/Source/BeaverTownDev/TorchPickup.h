// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "TorchPickup.generated.h"

class AMainCharacter;

UCLASS()
class BEAVERTOWNDEV_API ATorchPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATorchPickup();

private:
	UStaticMeshComponent* MeshRef = nullptr;
	AMainCharacter* CharRef = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable, Category = "Torch")
		void Initialize(UStaticMeshComponent* MeshToSet);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite)
		bool IsHeld = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool IsLit;

	//UPROPERTY(EditAnywhere, Category = "TorchSetup")
	//	USceneComponent* TorchRoot = nullptr;
	//UPROPERTY(EditAnywhere, Category = "TorchSetup")
	//	UStaticMeshComponent* TorchMesh = nullptr;
	//UPROPERTY(EditAnywhere, Category = "TorchSetup")
	//	UPointLightComponent* TorchLight = nullptr;
	//UPROPERTY(EditAnywhere, Category = "TorchSetup")
	//	UBoxComponent* TorchOverlap = nullptr;
	//UPROPERTY(EditAnywhere, Category = "TorchSetup")
	//	UCapsuleComponent* TorchCollision = nullptr;
	//UPROPERTY(EditAnywhere, Category = "TorchSetup")
	//	USphereComponent* TorchIgniteOverlap = nullptr;

	UFUNCTION(BlueprintImplementableEvent, Category = "Torch")
		void PickUpTorch();
	UFUNCTION(BlueprintImplementableEvent, Category = "Torch")
		void DropTorch();
	
};
