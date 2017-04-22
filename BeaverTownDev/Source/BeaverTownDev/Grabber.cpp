
#include "BeaverTownDev.h"
#include "Grabber.h"
#include "MainCharacter.h"
#include "ThrowableItems.h"
#include "TorchPickup.h"
#include "PushableObject.h"
#include "ThrowableRock.h"
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
			if (Actor->GetClass()->IsChildOf(ATorchPickup::StaticClass()))
			{
				TorchToHold = Cast<ATorchPickup>(Actor);
				TorchToHold->PickUpTorch();
				IsHeld = true;
				break;
			}
		}

		if (ItemToThrow && IsHeld == false)
		{
			IsHeld = true;
			auto ItemToGrab = ItemToThrow->FindComponentByClass<UStaticMeshComponent>();
			//ItemToGrab->SetCollisionProfileName(TEXT("IgnorePawnOnly"));
			FVector ItemLocation = ItemToGrab->GetOwner()->GetActorLocation();
			FRotator ItemRotation = ItemToGrab->GetOwner()->GetActorRotation();

			PhysicsHandle->GrabComponentAtLocationWithRotation(ItemToGrab, NAME_None, ItemLocation, ItemRotation);
			ItemToThrow->SetActorEnableCollision(false);
			
		}

		if (ObjectToPush)
		{
			IsHeld = true;
			auto ItemToGrab = ObjectToPush->FindComponentByClass<UStaticMeshComponent>();
			ItemToGrab->SetCollisionProfileName(TEXT("IgnorePawnOnly"));
			FVector ItemLocation = ItemToGrab->GetOwner()->GetActorLocation();
			FRotator ItemRotation = ItemToGrab->GetOwner()->GetActorRotation();

			AMainCharacter* Char = Cast<AMainCharacter>(GetOwner());
			if (Char)
			{
				Char->SetIsPushingObject(true);
				Char->SetMaxWalkSpeed(150.f);
				PhysicsHandle->GrabComponentAtLocation(ItemToGrab, NAME_None, GetOwner()->GetActorLocation() + FVector(0,0,-50.f));
				IsHeld = true;
			}			
		}
	}
}

void UGrabber::Release()
{
	// For Torch
	if (IsHeld && TorchToHold)
	{
		TorchToHold->DropTorch();
		TorchToHold = nullptr;
		IsHeld = false;
	}

	// For rest
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


void UGrabber::Throw()
{
	//// For Torch
	//if (IsHeld && TorchToHold)
	//{
	//	TorchToHold->DropTorch();
	//	TorchToHold = nullptr;
	//	IsHeld = false;
	//}

	// For rest
	if (PhysicsHandle && IsHeld && !TorchToHold)
	{	
		if (ItemToThrow)
		{
			UE_LOG(LogTemp, Warning, TEXT("Trying to THROW Object"))
			PhysicsHandle->GrabbedComponent->WakeRigidBody(NAME_None);
			PhysicsHandle->GrabbedComponent->AddImpulse(GetOwner()->GetActorForwardVector()*DefaultThrowForce, NAME_None, true);
			ItemToThrow->SetActorEnableCollision(true);
			ItemToThrow->SetIsThrown(true);
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

FHitResult UGrabber::LineTraceFromCharacter()
{
	FVector StartTrace = GetOwner()->GetActorLocation();
	FVector EndTrace = StartTrace + (GetOwner()->GetActorRotation().Vector() * Reach);
	EndTrace.Z -= 25.f;
	StartTrace.Z -= 25.f;

	FCollisionQueryParams QueryParams(FName(TEXT("")), false, GetOwner());
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByObjectType(
		HitResult,
		StartTrace,
		EndTrace,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), QueryParams
		);

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
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing InputComponent"), *GetOwner()->GetName())
	}
}

