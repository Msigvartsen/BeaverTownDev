// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "PushableObject.h"
#include "MainCharacter.h"

// Sets default values
APushableObject::APushableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	/*Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = Mesh;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ForwardTrigger"));
	BoxCollision->SetupAttachment(GetRootComponent());
	BoxCollision->bGenerateOverlapEvents = true;*/

	//RootComponent = BoxCollision;
	

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


void APushableObject::SetIgnorePlayerCollision(bool IsCollisionActive)
{
	/*BoxCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	auto PlayerRef = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	BoxCollision->IgnoreActorWhenMoving(PlayerRef, IsCollisionActive);*/
}