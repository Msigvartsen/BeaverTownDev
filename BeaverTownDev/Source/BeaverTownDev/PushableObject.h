
#pragma once

#include "GameFramework/Actor.h"
#include "PushableObject.generated.h"

UCLASS()
class BEAVERTOWNDEV_API APushableObject : public AActor
{
	GENERATED_BODY()
	
public:	

	APushableObject();
	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;
	

private:
	USceneComponent* Root = nullptr;
	UPROPERTY(EditDefaultsOnly)
		UBoxComponent* ForwardTrigger = nullptr;

	UPROPERTY(EditDefaultsOnly)
		UBoxComponent* RightTrigger = nullptr;

public:
	UFUNCTION()
	void OnForwardOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
		UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult &SweepResult);
	
	UFUNCTION()
		void OnRightOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
			UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult &SweepResult);
	
	UFUNCTION()
		void OnForwardEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
	
	UFUNCTION()
		void OnRightEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
};
