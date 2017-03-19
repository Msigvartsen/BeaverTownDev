
#include "BeaverTownDev.h"
#include "Grabber.h"
#include "MainCharacter.h"
#include "ThrowableItems.h"
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
		PhysicsHandle->SetTargetLocationAndRotation(EndTrace, GetOwner()->GetActorRotation());	
	}
}

void UGrabber::Grab()
{
	// ting jeg adda
	///----------------------------------------------------------------------
	auto CharacterCollision = GetOwner()->FindComponentByClass<UCapsuleComponent>();
	TArray<AActor*> OverlappingActors;
	AThrowableItems *ItemToThrow = nullptr;
	UE_LOG(LogTemp, Warning, TEXT("Calling Grab"))
		UE_LOG(LogTemp, Warning, TEXT("TEST1"))

	if (CharacterCollision)
	{
		UE_LOG(LogTemp, Warning, TEXT("TEST2"))
		CharacterCollision->GetOverlappingActors(OverlappingActors);
		for (AActor* Actor : OverlappingActors)
		{
			if (Actor->GetClass()->IsChildOf(AThrowableItems::StaticClass()))
			{
				UE_LOG(LogTemp, Warning, TEXT("TEST3"))
				ItemToThrow = Cast<AThrowableItems>(Actor);
				UE_LOG(LogTemp, Warning, TEXT("FOUND: %s"), *ItemToThrow->GetName())
			}
		}
		// TODO Make ItemToThrow able to hurt enemies
		if (ItemToThrow)
		{
			IsHeld = true;
			auto ItemToGrab = ItemToThrow->FindComponentByClass<UStaticMeshComponent>();
			FVector ItemLocation = ItemToGrab->GetOwner()->GetActorLocation();
			FRotator ItemRotation = ItemToGrab->GetOwner()->GetActorRotation();

			PhysicsHandle->GrabComponentAtLocationWithRotation(ItemToGrab, NAME_None, ItemLocation, ItemRotation);
			//PhysicsHandle->GrabComponent(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), true);
			//PhysicsHandle->GrabComponent(ItemToThrow->GetRootPrimitiveComponent(), EName::NAME_None, GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * 100.f, true);
		}
	}
	///----------------------------------------------------------------------

	if (PhysicsHandle) 
	{
		FHitResult HitResult = LineTraceFromCharacter();
		ComponentToGrab = HitResult.GetComponent();
		AActor* ActorHit = HitResult.GetActor();
		if (ActorHit)
		{
			IsHeld = true;
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
		IsHeld = false;
	}
}

void UGrabber::Throw()
{
	if (PhysicsHandle && IsHeld)
	{	
		UE_LOG(LogTemp, Warning, TEXT("Trying to THROW Object"))	
		PhysicsHandle->GrabbedComponent->WakeRigidBody(NAME_None);
		PhysicsHandle->GrabbedComponent->AddImpulse(GetOwner()->GetActorForwardVector()*2000.f, NAME_None, true);
		PhysicsHandle->ReleaseComponent();	
		IsHeld = false;
			
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
		//UE_LOG(LogTemp, Warning, TEXT("Hit %s"), *ActorHit->GetName());

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
		InputComponent->BindAction("Melee", IE_Pressed, this, &UGrabber::Throw);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing InputComponent"), *GetOwner()->GetName())
	}
}