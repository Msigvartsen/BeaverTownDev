// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Raft.generated.h"

class AMainCharacter;
class ABeaverTownDevGameModeBase;

UCLASS()
class BEAVERTOWNDEV_API ARaft : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARaft();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = Raft)
		void MoveRaftTowardPlayer();

private:
	UPROPERTY(EditAnywhere)
		USceneComponent* RaftRoot;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* RaftMesh;
	UPROPERTY(EditAnywhere)
		UBoxComponent* ForwardTrigger;
	UPROPERTY(EditAnywhere)
		UBoxComponent* BackwardTrigger;
	UPROPERTY(EditAnywhere)
		UBoxComponent* RightTrigger;
	UPROPERTY(EditAnywhere)
		UBoxComponent* LeftTrigger;

	AMainCharacter* PlayerCharacter;
	ABeaverTownDevGameModeBase* GameMode = nullptr;
	UPrimitiveComponent* RaftPrimitive;

	void ResetTimer();
	bool RightAngle(FName Name);
	bool AngleTest(float PlayerYaw, float RaftYaw, float AcceptedAngle);
	bool RightAngleWithDotProduct(FName Name);
	bool DotProductTest(FVector Vector1, FVector Vector2);
	float AcceptedAngle = 45.f;

	bool bTimerReady = true;
	FTimerHandle TimerHandle;
	FVector TargetLocation;
	FVector CurrentLocation;
	FHitResult RaftHitResult;

	UPROPERTY(EditDefaultsOnly)
		float Timer = .3f;
	UPROPERTY(EditDefaultsOnly)
		float Speed = 500.f;
	UPROPERTY(EditDefaultsOnly)
		float Force = 5000.f;

};
