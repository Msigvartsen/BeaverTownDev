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
}

// Called every frame
void ARaft::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Forward)
	{
		FVector TargetLocation = GetActorLocation();
		TargetLocation.X += 10.f;
		FVector NewLocation = FMath::VInterpTo(GetActorLocation(), TargetLocation, GetWorld()->GetDeltaSeconds(), 1.f);
		SetActorLocation(TargetLocation);

	}

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
		Forward = true;

}

void ARaft::OnBackwardOverlap(UPrimitiveComponent* OverlappingComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Backward"))

	//Move raft Backward

}

void ARaft::OnRightOverlap(UPrimitiveComponent* OverlappingComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Right"))

	//Move raft Right

}

void ARaft::OnLeftOverlap(UPrimitiveComponent* OverlappingComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Left"))

	//Move raft Left

}

