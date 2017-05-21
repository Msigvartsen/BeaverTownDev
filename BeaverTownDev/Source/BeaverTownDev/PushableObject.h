
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
	
};
