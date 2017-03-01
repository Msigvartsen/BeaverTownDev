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
	RaftMesh->IgnoreActorWhenMoving(PlayerCharacter, true);

	/// TODO add force movement instead of static
	RaftMesh->SetSimulatePhysics(true);
	RaftMesh->WakeRigidBody();
	RaftMesh->SetEnableGravity(false);



}

// Called every frame
void ARaft::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (bTimerReady && PlayerCharacter->GetIsInteractActive() && ForwardTrigger->IsOverlappingActor(PlayerCharacter) && RightAngle(FName("Forward")))
	{
		bTimerReady = false;
		TargetLocation -= GetActorForwardVector() * Speed;
		CurrentLocation = GetActorLocation();
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ARaft::ResetTimer, Timer, false);
	}
	else if (bTimerReady && PlayerCharacter->GetIsInteractActive() && BackwardTrigger->IsOverlappingActor(PlayerCharacter) && RightAngle(FName("Backward")))
	{
		bTimerReady = false;
		TargetLocation += GetActorForwardVector() * Speed;
		CurrentLocation = GetActorLocation();
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ARaft::ResetTimer, Timer, false);
	}
	else if (bTimerReady && PlayerCharacter->GetIsInteractActive() && LeftTrigger->IsOverlappingActor(PlayerCharacter) && RightAngle(FName("Left")))
	{
		bTimerReady = false;
		TargetLocation += GetActorRightVector() * Speed;
		CurrentLocation = GetActorLocation();
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ARaft::ResetTimer, Timer, false);
	}
	else if (bTimerReady && PlayerCharacter->GetIsInteractActive() && RightTrigger->IsOverlappingActor(PlayerCharacter) && RightAngle(FName("Right")))
	{
		bTimerReady = false;
		TargetLocation -= GetActorRightVector() * Speed;;
		CurrentLocation = GetActorLocation();
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ARaft::ResetTimer, Timer, false);
	}

	FVector NewLocation = FMath::VInterpTo(GetActorLocation(), TargetLocation, DeltaTime, 1.f);
	SetActorLocation(NewLocation, true, &RaftHitResult);

	if (RaftHitResult.GetActor())
	{
		TargetLocation = GetActorLocation();
	}
}

// Returns true if the Player has the correct angle to interact with raft
bool ARaft::RightAngle(FName Name)
{
	float PlayerYaw = PlayerCharacter->GetActorRotation().Yaw;
	UE_LOG(LogTemp, Warning, TEXT("PlayerYaw: %f"), PlayerYaw)

	if (Name == "Forward")
	{
		if (PlayerYaw > 0.f - AcceptedAngle && PlayerYaw < 0.f + AcceptedAngle)
		{
			return true;
		}
	}
	else if (Name == "Backward")
	{
		if ((PlayerYaw < -180.f + AcceptedAngle && PlayerYaw > -180.f) || (PlayerYaw > 180.f - AcceptedAngle && PlayerYaw < 180.f))
		{
			return true;
		}
	}
	else if (Name == "Left")
	{
		if (PlayerYaw < -45.f && PlayerYaw > -180.f + AcceptedAngle)
		{
			return true;
		}
	}
	else if (Name == "Right")
	{
		if (PlayerYaw > 45.f && PlayerYaw < 180.f - AcceptedAngle)
		{
			return true;
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid Player Angle"))
	}
	return false;
}

void ARaft::ResetTimer()
{
	bTimerReady = true;
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}
