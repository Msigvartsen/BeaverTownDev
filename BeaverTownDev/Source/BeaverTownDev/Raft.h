// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Raft.generated.h"

class AMainCharacter;

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

	UFUNCTION()
		void OnForwardOverlap(UPrimitiveComponent* OverlappingComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	UFUNCTION()
		void OnBackwardOverlap(UPrimitiveComponent* OverlappingComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	UFUNCTION()
		void OnRightOverlap(UPrimitiveComponent* OverlappingComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	UFUNCTION()
		void OnLeftOverlap(UPrimitiveComponent* OverlappingComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);


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

	bool bForward = false;
	bool bBackward = false;
	bool bLeft = false;
	bool bRight = false;

	void ResetTimer();
	bool RightAngle(FName Name);
	float AcceptedAngle = 45.f;

	bool bTimerReady = true;
	FTimerHandle TimerHandle;
	FVector TargetLocation;
	FVector CurrentLocation;

	UPROPERTY(EditAnywhere)
		float Timer = .3f;
	UPROPERTY(EditAnywhere)
		float Speed = 500.f;

};
