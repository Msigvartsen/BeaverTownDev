// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "MainCharacter.h"
#include "Raft.h"


// Sets default values
ARaft::ARaft()
{
	PrimaryActorTick.bCanEverTick = true;

	RaftMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RaftMesh"));
	RaftMesh->SetupAttachment(RootComponent);

	ForwardTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("ForwardTrigger"));
	ForwardTrigger->SetCollisionProfileName(FName("OverlapAll"));
	ForwardTrigger->bGenerateOverlapEvents = true;
	ForwardTrigger->SetupAttachment(RaftMesh);

	BackwardTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BackwardTrigger"));
	BackwardTrigger->SetCollisionProfileName(FName("OverlapAll"));
	BackwardTrigger->bGenerateOverlapEvents = true;
	BackwardTrigger->SetupAttachment(RaftMesh);

	RightTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("RightTrigger"));
	RightTrigger->SetCollisionProfileName(FName("OverlapAll"));
	RightTrigger->bGenerateOverlapEvents = true;
	RightTrigger->SetupAttachment(RaftMesh);

	LeftTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftTrigger"));
	LeftTrigger->SetCollisionProfileName(FName("OverlapAll"));
	LeftTrigger->bGenerateOverlapEvents = true;
	LeftTrigger->SetupAttachment(RaftMesh);
	
}

// Called when the game starts or when spawned
void ARaft::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	TargetLocation = GetActorForwardVector();

	//RaftMesh->IgnoreActorWhenMoving(PlayerCharacter, true);
	RaftMesh->SetSimulatePhysics(true);
	RaftMesh->WakeRigidBody();
	RaftMesh->SetEnableGravity(true);
	RaftMesh->SetMassOverrideInKg(FName(""), 100.f, true);
	RaftMesh->SetAngularDamping(0.f);
	RaftMesh->SetLinearDamping(1.f);

	RaftPrimitive = Cast<UPrimitiveComponent>(GetRootComponent());

	
}

// Called every frame
void ARaft::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bTimerReady && PlayerCharacter->GetIsInteractActive() && ForwardTrigger->IsOverlappingActor(PlayerCharacter) && RightAngle(FName("Forward")))
	{
		bTimerReady = false;
		//TargetLocation -= GetActorForwardVector() * Speed;
		//CurrentLocation = GetActorLocation();

		if (RaftPrimitive)
		{
			auto ForceApplied = GetActorForwardVector() * RaftMesh->GetMass() * -1.f * Force;
			auto LocationApplied = ForwardTrigger->RelativeLocation;
			RaftPrimitive->AddForceAtLocation(ForceApplied, LocationApplied);
			UE_LOG(LogTemp, Warning, TEXT("Forward Force Added"))
		}

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ARaft::ResetTimer, Timer, false);
	}
	else if (bTimerReady && PlayerCharacter->GetIsInteractActive() && BackwardTrigger->IsOverlappingActor(PlayerCharacter) && RightAngle(FName("Backward")))
	{
		bTimerReady = false;
		//TargetLocation += GetActorForwardVector() * Speed;
		//CurrentLocation = GetActorLocation();

		if (RaftPrimitive)
		{
			auto ForceApplied = GetActorForwardVector() * RaftMesh->GetMass() * 1.f * Force;
			auto LocationApplied = BackwardTrigger->RelativeLocation;
			RaftPrimitive->AddForceAtLocation(ForceApplied, LocationApplied);
			UE_LOG(LogTemp, Warning, TEXT("Backward Force Added"))
		}

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ARaft::ResetTimer, Timer, false);
	}
	else if (bTimerReady && PlayerCharacter->GetIsInteractActive() && LeftTrigger->IsOverlappingActor(PlayerCharacter) && RightAngle(FName("Left")))
	{
		bTimerReady = false;
		//TargetLocation += GetActorRightVector() * Speed;
		//CurrentLocation = GetActorLocation();

		if (RaftPrimitive)
		{
			auto ForceApplied = GetActorRightVector() * RaftMesh->GetMass() * 1.f * Force;
			auto LocationApplied = LeftTrigger->RelativeLocation;
			RaftPrimitive->AddForceAtLocation(ForceApplied, LocationApplied);
			UE_LOG(LogTemp, Warning, TEXT("Left Force Added"))
		}

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ARaft::ResetTimer, Timer, false);
	}
	else if (bTimerReady && PlayerCharacter->GetIsInteractActive() && RightTrigger->IsOverlappingActor(PlayerCharacter) && RightAngle(FName("Right")))
	{
		bTimerReady = false;
		//TargetLocation -= GetActorRightVector() * Speed;;
		//CurrentLocation = GetActorLocation();

		if (RaftPrimitive)
		{
			auto ForceApplied = GetActorRightVector() * RaftMesh->GetMass() * -1.f * Force;
			auto LocationApplied = RightTrigger->RelativeLocation;
			RaftPrimitive->AddForceAtLocation(ForceApplied, LocationApplied);
			UE_LOG(LogTemp, Warning, TEXT("Right Force Added"))
		}

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ARaft::ResetTimer, Timer, false);
	}

	//FVector NewLocation = FMath::VInterpTo(GetActorLocation(), TargetLocation, DeltaTime, 1.f);
	//SetActorLocation(NewLocation, true, &RaftHitResult);

	//if (RaftHitResult.GetActor())
	//{
	//	TargetLocation = GetActorLocation();
	//}
}

// Returns true if the Player has the correct angle to interact with raft
bool ARaft::RightAngle(FName Name)
{
	FVector RaftVector;
	float RaftYaw = GetActorRotation().Yaw;
	float PlayerYaw = PlayerCharacter->GetActorRotation().Yaw;

	if (Name == "Forward")
	{
		RaftVector = GetActorForwardVector();
		RaftYaw = RaftVector.Rotation().Yaw;
		return AngleTest(PlayerYaw, RaftYaw, AcceptedAngle);
	}
	else if (Name == "Backward")
	{
		RaftVector = GetActorForwardVector() * -1.f;
		RaftYaw = RaftVector.Rotation().Yaw;
		return AngleTest(PlayerYaw, RaftYaw, AcceptedAngle);
	}
	else if (Name == "Left")
	{
		RaftVector = GetActorRightVector() * -1.f;
		RaftYaw = RaftVector.Rotation().Yaw;
		return AngleTest(PlayerYaw, RaftYaw, AcceptedAngle);
	}
	else if (Name == "Right")
	{
		RaftVector = GetActorRightVector();
		RaftYaw = RaftVector.Rotation().Yaw;
		return AngleTest(PlayerYaw, RaftYaw, AcceptedAngle);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid Player Angle"))
	}
	return false;
}

bool ARaft::AngleTest(float PlayerYaw, float RaftYaw, float InAcceptedAngle)
{
	float MinAngle = RaftYaw - InAcceptedAngle;
	float MaxAngle = RaftYaw + InAcceptedAngle;
	bool MinAngleChanged = false;
	bool MaxAngleChanged = false;

	if (MinAngle < -180.f)
	{
		MinAngle = MinAngle + 360.f;
		MinAngleChanged = true;
	}
	if (MaxAngle > 180.f)
	{
		MaxAngle = MaxAngle - 360.f;
		MaxAngleChanged = true;
	}

	if (MaxAngleChanged)
	{
		if ((PlayerYaw < MaxAngle && PlayerYaw > -180.f) || (PlayerYaw > MinAngle && PlayerYaw < 180.f))
		{
			return true;
		}
	}
	else if (MinAngleChanged)
	{
		if ((PlayerYaw > MinAngle && PlayerYaw < 180.f) || (PlayerYaw < MaxAngle && PlayerYaw > -180.f))
		{
			return true;
		}
	}
	else
	{
		if (PlayerYaw > MinAngle && PlayerYaw < MaxAngle)
		{
			return true;
		}
	}
	return false;
}

void ARaft::ResetTimer()
{
	bTimerReady = true;
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}
