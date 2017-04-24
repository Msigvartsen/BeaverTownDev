// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "FloatingCrate.h"


// Sets default values
AFloatingCrate::AFloatingCrate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//FloatingCrateRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	//RootComponent = FloatingCrateRoot;
	FloatingCrateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	FloatingCrateMesh->SetupAttachment(RootComponent);

	//FloatingCrateArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ARROW"));
	//FloatingCrateArrow->SetupAttachment(FloatingCrateMesh);

}

// Called when the game starts or when spawned
void AFloatingCrate::BeginPlay()
{
	Super::BeginPlay();
	
	FloatingCrateMesh->SetSimulatePhysics(true);
	FloatingCrateMesh->WakeRigidBody();
	FloatingCrateMesh->SetEnableGravity(true);
	FloatingCrateMesh->SetAngularDamping(1.f);
	FloatingCrateMesh->SetLinearDamping(1.f);
	FloatingCrateMesh->SetMassOverrideInKg(FName(""), 100.f, true);
	FloatingCrateMesh->SetConstraintMode(EDOFMode::XYPlane);

	FloatingCratePrimitive = Cast<UPrimitiveComponent>(GetRootComponent());
}

// Called every frame
void AFloatingCrate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFloatingCrate::MoveCrate(FVector Direction)
{
	FVector ForceApplied = Direction * FloatingCrateMesh->GetMass() * Force;
	FVector Location = FloatingCrateMesh->GetSocketLocation(FName("SpawnLocation"));

	if (FloatingCratePrimitive)
	{
		UE_LOG(LogTemp, Warning, TEXT("PUSHING"))
		FloatingCratePrimitive->AddForceAtLocation(ForceApplied, Location);
	}
	
}

void AFloatingCrate::MakeFall()
{
	FloatingCrateMesh->SetConstraintMode(EDOFMode::None);
}
