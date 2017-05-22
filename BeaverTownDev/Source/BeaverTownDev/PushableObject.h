
#pragma once

#include "GameFramework/Actor.h"
#include "PushableObject.generated.h"

/*
Boxes that cna be pushed will derive from this class
The class i used to provide an easy way for grabber.cpp to find all pushable objects
The class itself has no functionality because we only have one class that can be pushed
*/

UCLASS()
class BEAVERTOWNDEV_API APushableObject : public AActor
{
	GENERATED_BODY()
	
public:	
	APushableObject();
};
