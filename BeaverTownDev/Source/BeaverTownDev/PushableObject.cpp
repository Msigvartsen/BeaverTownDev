// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "PushableObject.h"


// Sets default values
APushableObject::APushableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	RootComponent = Root;

	ForwardTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("ForwardTrigger"));
	ForwardTrigger->SetupAttachment(GetRootComponent());
	ForwardTrigger->bGenerateOverlapEvents = true;
	ForwardTrigger->OnComponentBeginOverlap.AddDynamic(this, &APushableObject::OnForwardOverlap);
	ForwardTrigger->OnComponentEndOverlap.AddDynamic(this, &APushableObject::OnForwardEndOverlap);

	RightTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("RightTrigger"));
	RightTrigger->SetupAttachment(GetRootComponent());
	RightTrigger->OnComponentBeginOverlap.AddDynamic(this, &APushableObject::OnRightOverlap);
	RightTrigger->OnComponentEndOverlap.AddDynamic(this, &APushableObject::OnRightEndOverlap);

}

// Called when the game starts or when spawned
void APushableObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APushableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APushableObject::OnForwardOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{

}

void APushableObject::OnForwardEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}


void APushableObject::OnRightOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{

}

void APushableObject::OnRightEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}