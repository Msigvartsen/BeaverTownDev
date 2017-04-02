
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
		UBoxComponent* BoxCollision = nullptr;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh = nullptr;

	bool CanMoveForward = false;
	bool CanMoveRight = false;
	bool IsCollisionActive = false;

public:
	

	UFUNCTION()
	void SetIgnorePlayerCollision(bool IsCollisionActive);
};
