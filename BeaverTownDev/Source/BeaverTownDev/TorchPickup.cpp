// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "MainCharacter.h"
#include "TorchPickup.h"


// Sets default values
ATorchPickup::ATorchPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//// Mesh and Root
	//TorchRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Torch Root"));
	//RootComponent = TorchRoot;
	//TorchMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Torch Mesh"));
	//TorchMesh->SetupAttachment(RootComponent);
	//TorchMesh->SetSimulatePhysics(true);
	//TorchMesh->WakeRigidBody();

	//// Point Light
	//TorchLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Torch Light"));
	//TorchLight->SetupAttachment(TorchMesh);
	//TorchLight->Activate();
	//TorchLight->SetIntensity(10000.f);

	//// Collisions
	//TorchCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Torch Blocking Collision"));
	//TorchCollision->SetupAttachment(RootComponent);
	//TorchOverlap = CreateDefaultSubobject<UBoxComponent>(TEXT("Torch Pickup Collision"));
	//TorchOverlap->SetupAttachment(RootComponent);
	//TorchIgniteOverlap = CreateDefaultSubobject<USphereComponent>(TEXT("Torch Ignite Collision"));
	//TorchIgniteOverlap->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATorchPickup::BeginPlay()
{
	Super::BeginPlay();
	CharRef = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());

}

// Called every frame
void ATorchPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsHeld)
	{
		if (MeshRef)
		{
			SetActorLocation(CharRef->GetMesh()->GetSocketLocation(FName("hand_r")));
			SetActorRotation(FRotator(0.f, CharRef->GetActorRotation().Yaw - 45.f, 20.f));
		}
	}
}

void ATorchPickup::Initialize(UStaticMeshComponent* MeshToSet)
{
	MeshRef = MeshToSet;
}
