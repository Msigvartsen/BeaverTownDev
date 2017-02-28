// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "MainCharacter.h"
#include "Raft.h"


// Sets default values
ARaft::ARaft()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RaftMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RaftMesh"));
	RaftMesh->SetupAttachment(RootComponent);

	ForwardTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("ForwardTrigger"));
	ForwardTrigger->SetCollisionProfileName(FName("OverlapAll"));
	ForwardTrigger->bGenerateOverlapEvents = true;
	ForwardTrigger->OnComponentBeginOverlap.AddDynamic(this, &ARaft::OnForwardOverlap);
	ForwardTrigger->SetupAttachment(RaftMesh);

	BackwardTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BackwardTrigger"));
	BackwardTrigger->SetCollisionProfileName(FName("OverlapAll"));
	BackwardTrigger->bGenerateOverlapEvents = true;
	BackwardTrigger->OnComponentBeginOverlap.AddDynamic(this, &ARaft::OnBackwardOverlap);
	BackwardTrigger->SetupAttachment(RaftMesh);

	RightTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("RightTrigger"));
	RightTrigger->SetCollisionProfileName(FName("OverlapAll"));
	RightTrigger->bGenerateOverlapEvents = true;
	RightTrigger->OnComponentBeginOverlap.AddDynamic(this, &ARaft::OnRightOverlap);
	RightTrigger->SetupAttachment(RaftMesh);

	LeftTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftTrigger"));
	LeftTrigger->SetCollisionProfileName(FName("OverlapAll"));
	LeftTrigger->bGenerateOverlapEvents = true;
	LeftTrigger->OnComponentBeginOverlap.AddDynamic(this, &ARaft::OnLeftOverlap);
	LeftTrigger->SetupAttachment(RaftMesh);
	
	
}

// Called when the game starts or when spawned
void ARaft::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	TargetLocation = GetActorLocation();
}

// Called every frame
void ARaft::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// TODO add force movement instead of static

	if (bTimerReady && PlayerCharacter->GetIsInteractActive() && ForwardTrigger->IsOverlappingActor(PlayerCharacter) && RightAngle(FName("Forward")))
	{
		bTimerReady = false;
		TargetLocation = GetActorLocation();
		TargetLocation.X -= Speed;
		CurrentLocation = GetActorLocation();

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ARaft::ResetTimer, Timer, false);
	}

	if (bTimerReady && PlayerCharacter->GetIsInteractActive() && BackwardTrigger->IsOverlappingActor(PlayerCharacter) && RightAngle(FName("Backward")))
	{
		bTimerReady = false;
		TargetLocation = GetActorLocation();
		TargetLocation.X += Speed;
		CurrentLocation = GetActorLocation();

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ARaft::ResetTimer, Timer, false);
	}

	if (bTimerReady && PlayerCharacter->GetIsInteractActive() && LeftTrigger->IsOverlappingActor(PlayerCharacter) && RightAngle(FName("Left")))
	{
		bTimerReady = false;
		TargetLocation = GetActorLocation();
		TargetLocation.Y += Speed;
		CurrentLocation = GetActorLocation();

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ARaft::ResetTimer, Timer, false);
	}

	if (bTimerReady && PlayerCharacter->GetIsInteractActive() && RightTrigger->IsOverlappingActor(PlayerCharacter) && RightAngle(FName("Right")))
	{	UE_LOG(LogTemp, Warning, TEXT("Forward"))

		bTimerReady = false;
		TargetLocation = GetActorLocation();
		TargetLocation.Y -= Speed;
		CurrentLocation = GetActorLocation();

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ARaft::ResetTimer, Timer, false);
	}
	FVector NewLocation = FMath::VInterpTo(GetActorLocation(), TargetLocation, DeltaTime, 1.f);
	SetActorLocation(NewLocation);
}

void ARaft::OnForwardOverlap(UPrimitiveComponent* OverlappingComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Forward"))
	///Move raft Forward
	//RaftMesh->SetSimulatePhysics(true);
	//RaftMesh->WakeRigidBody();
	//RaftMesh->SetEnableGravity(true);

	/*if (PlayerCharacter->GetIsInteractActive())
	{
		Forward = true;
	}*/
	bForward = true;

}

void ARaft::OnBackwardOverlap(UPrimitiveComponent* OverlappingComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Backward"))

	//Move raft Backward

	bBackward = true;

}

void ARaft::OnRightOverlap(UPrimitiveComponent* OverlappingComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Right"))

	//Move raft Right

	bRight = true;

}

void ARaft::OnLeftOverlap(UPrimitiveComponent* OverlappingComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Left"))

	//Move raft Left

	bLeft = true;

}

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
