// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "Pickup.h"


// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickupRoot = CreateDefaultSubobject<USceneComponent>(TEXT("PickupRoot"));
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	PickupBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = PickupRoot;
	PickupMesh->SetupAttachment(RootComponent);
	PickupBox->SetupAttachment(RootComponent);
	PickupBox->bGenerateOverlapEvents = true;
	PickupBox->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnOverlap);
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickup::OnOverlap(UPrimitiveComponent* OverlappingComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	// her kan vi legge objektet til inventory
	Destroy();
}

