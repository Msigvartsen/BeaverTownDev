// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverTownDev.h"
#include "Projectile.h"
#include "EnemyBase.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//ProjectileRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileRoot"));

	ProjectileRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileRoot"));
	RootComponent = ProjectileRoot;
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectileCollision"));
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileCollision->SetupAttachment(RootComponent);
	ProjectileCollision->bGenerateOverlapEvents = true;
	ProjectileCollision->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlap);

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LaunchProjectile(DeltaTime);
}

void AProjectile::LaunchProjectile(float DeltaTime)
{
	FVector NewLocation = GetActorLocation();
	NewLocation += GetActorForwardVector() * ProjectileSpeed * DeltaTime;
	SetActorLocation(NewLocation);
	DespawnTime -= DeltaTime;
	if (DespawnTime < 0)
	{
		Destroy();
	}
	
}

void AProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlapped with: %s"), *OtherActor->GetName())

	if(OtherActor->IsA(AEnemyBase::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy Hit"))
		AEnemyBase* EnemyHit = Cast<AEnemyBase>(OtherActor);
		if (!EnemyHit) { return; }
		EnemyHit->RemoveHealth(ProjectileDamage);
		Destroy();
	}
}
