// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "EnemyBase.h"
#include "ComplexProjectile.h"


// Sets default values
AComplexProjectile::AComplexProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ComplexProjectileRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = ComplexProjectileRoot;
	ComplexProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	ComplexProjectileCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	ComplexProjectileMesh->SetupAttachment(RootComponent);
	ComplexProjectileCollision->SetupAttachment(RootComponent);
	ComplexProjectileCollision->SetCollisionProfileName(FName("BlockAll"));
	ComplexProjectileCollision->bGenerateOverlapEvents = true;
	ComplexProjectileCollision->OnComponentBeginOverlap.AddDynamic(this, &AComplexProjectile::OnOverlap);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovement->bAutoActivate = false;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

}

// Called when the game starts or when spawned
void AComplexProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AComplexProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AComplexProjectile::Shoot(float Speed)
{
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovement->Activate();
}

void AComplexProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlapped with"))

	if (OtherActor->IsA(AEnemyBase::StaticClass()))
	{
		AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor);
		Enemy->RemoveHealth(25);
	}

	//GetWorld()->DestroyActor(this); //crashes the editor

}