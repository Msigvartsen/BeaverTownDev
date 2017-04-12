
#include "BeaverTownDev.h"
#include "Grabber.h"
#include "MainCharacter.h"
#include "ThrowableItems.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "PushableObject.h"

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
	if (StartThrow && ThrowForce < 2500.f)
	{
		ThrowForce += 500 * DeltaTime;
		UE_LOG(LogTemp, Warning, TEXT("ThrowForce adds up ? : %f"), ThrowForce)
	}
}

void UGrabber::Grab()
{

	auto CharacterCollision = GetOwner()->FindComponentByClass<UCapsuleComponent>();
	TArray<AActor*> OverlappingActors;

	UE_LOG(LogTemp, Warning, TEXT("Calling Grab"))

	if (CharacterCollision && IsHeld == false)
	{
		CharacterCollision->GetOverlappingActors(OverlappingActors);
		for (AActor* Actor : OverlappingActors)
		{
			if (Actor->GetClass()->IsChildOf(AThrowableItems::StaticClass()))
			{
				ItemToThrow = Cast<AThrowableItems>(Actor);
			}
			if (Actor->IsA(APushableObject::StaticClass()))
			{
				ObjectToPush = Cast<APushableObject>(Actor);
			}
		}

		if (ItemToThrow)
		{
			auto ItemToGrab = ItemToThrow->FindComponentByClass<UStaticMeshComponent>();
			FVector ItemLocation = ItemToGrab->GetOwner()->GetActorLocation();
			FRotator ItemRotation = ItemToGrab->GetOwner()->GetActorRotation();

			PhysicsHandle->GrabComponentAtLocationWithRotation(ItemToGrab, NAME_None, ItemLocation, ItemRotation);
			ItemToThrow->SetActorEnableCollision(false);
			IsHeld = true;
		}

		if (ObjectToPush)
		{
			ObjectToPush->SetActorEnableCollision(false);
			IsHeld = true;
			auto ItemToGrab = ObjectToPush->FindComponentByClass<UStaticMeshComponent>();
			FVector ItemLocation = ItemToGrab->GetOwner()->GetActorLocation();
			FRotator ItemRotation = ItemToGrab->GetOwner()->GetActorRotation();

			AMainCharacter* Char = Cast<AMainCharacter>(GetOwner());
			if (Char)
			{
				Char->SetIsPushingObject(true);
				Char->SetMaxWalkSpeed(200.f);
				
				PhysicsHandle->GrabComponentAtLocation(ItemToGrab, NAME_None, GetOwner()->GetActorLocation());
				IsHeld = true;
			}			
		}
	}
	// Temp for grabbing nonclass meshes
	if (PhysicsHandle && IsHeld == false)
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
			IsHeld = true;
		}
	}
}

void UGrabber::Release()
{
	if (PhysicsHandle)
	{
		if (ItemToThrow)
		{
			ItemToThrow->SetActorEnableCollision(true);
			ItemToThrow = nullptr;
		}
		if (ObjectToPush)
		{
			ObjectToPush->SetActorEnableCollision(true);
			ObjectToPush = nullptr;
		}
		PhysicsHandle->ReleaseComponent();
		IsHeld = false;
		AMainCharacter* Char = Cast<AMainCharacter>(GetOwner());
		if (Char)
		{
			Char->SetIsPushingObject(false);
			Char->SetMaxWalkSpeed(600.f);
		}		
	}
}

void UGrabber::ChargeThrow()
{
	if (PhysicsHandle && IsHeld)
	{
		if (ItemToThrow)
		{
			ItemToThrow->SetActorEnableCollision(true);
			ItemToThrow = nullptr;
		}
		if (ObjectToPush)
		{
			ObjectToPush->SetActorEnableCollision(true);
			ObjectToPush = nullptr;
		}
		StartThrow = true;
	}
	
}

void UGrabber::Throw()
{
	if (PhysicsHandle && IsHeld)
	{	
		if (ItemToThrow)
		{
			ItemToThrow->SetActorEnableCollision(true);
			ItemToThrow = nullptr;
		}
		if (ObjectToPush)
		{
			ObjectToPush->SetActorEnableCollision(true);
			ObjectToPush = nullptr;
		}
		UE_LOG(LogTemp, Warning, TEXT("Trying to THROW Object"))	
		PhysicsHandle->GrabbedComponent->WakeRigidBody(NAME_None);
		PhysicsHandle->GrabbedComponent->AddImpulse(GetOwner()->GetActorForwardVector()*ThrowForce, NAME_None, true);
		PhysicsHandle->ReleaseComponent();	
		IsHeld = false;
		StartThrow = false;
		ThrowForce = DefaultThrowForce;

		AMainCharacter* Char = Cast<AMainCharacter>(GetOwner());
		if (Char)
		{
			Char->SetIsPushingObject(false);
			Char->SetMaxWalkSpeed(600.f);
		}
	}
}

FHitResult UGrabber::LineTraceFromCharacter()
{
	FVector StartTrace = GetOwner()->GetActorLocation();
	FVector EndTrace = StartTrace + (GetOwner()->GetActorRotation().Vector() * Reach);
	EndTrace.Z -= 25.f;
	StartTrace.Z -= 25.f;

	// Draws a green line that represents the line trace
	//DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor(0, 255, 0), false, .3f, 0, 10.f);

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
		InputComponent->BindAction("Melee", IE_Released, this, &UGrabber::Throw);
		InputComponent->BindAction("Melee", IE_Pressed, this, &UGrabber::ChargeThrow);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing InputComponent"), *GetOwner()->GetName())
	}
}

