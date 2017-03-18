
#include "BeaverTownDev.h"
#include "Grabber.h"
#include "MainCharacter.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"


UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	
	FindPhysicsHandle();
	FindInputComponent();
}


void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	LineTraceFromCharacter();

	if (PhysicsHandle->GrabbedComponent)
	{
		FVector StartTrace = GetOwner()->GetActorLocation();
		FVector EndTrace = StartTrace + (GetOwner()->GetActorRotation().Vector() * Reach);
		EndTrace.Z -= 25.f;
		StartTrace.Z -= 25.f;
		if (!PhysicsHandle) { return; }
		PhysicsHandle->SetTargetLocationAndRotation(EndTrace,GetOwner()->GetActorRotation());	
	}
}

void UGrabber::Grab()
{
	if (PhysicsHandle) 
	{
		FHitResult HitResult = LineTraceFromCharacter();
		UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
		AActor* ActorHit = HitResult.GetActor();
		if (ActorHit)
		{
			FVector ComponentLocation = ComponentToGrab->GetOwner()->GetActorLocation();
			FRotator ComponentRotation = ComponentToGrab->GetOwner()->GetActorRotation();
			PhysicsHandle->GrabComponentAtLocationWithRotation(ComponentToGrab, NAME_None, ComponentLocation, ComponentRotation);
		}
	}
}

void UGrabber::Release()
{
	if (PhysicsHandle)
	{
		PhysicsHandle->ReleaseComponent();
	}
}

FHitResult UGrabber::LineTraceFromCharacter()
{
	FVector StartTrace = GetOwner()->GetActorLocation();
	FVector EndTrace = StartTrace + (GetOwner()->GetActorRotation().Vector() * Reach);
	EndTrace.Z -= 25.f;
	StartTrace.Z -= 25.f;

	// Draws a green line that represents the line trace
	DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor(0, 255, 0), false, .3f, 0, 10.f);

	 FCollisionQueryParams QueryParams(FName(TEXT("")), false, GetOwner());
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByObjectType(
		HitResult,
		StartTrace,
		EndTrace,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), QueryParams
		);

	AActor* ActorHit = HitResult.GetActor();

	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit %s"), *ActorHit->GetName());

	}
	return HitResult;
}

void UGrabber::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing PhysicsHandle component"), *GetOwner()->GetName())
	}
}

void UGrabber::FindInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Interact", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Shoot", IE_Pressed, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing InputComponent"), *GetOwner()->GetName())
	}
}