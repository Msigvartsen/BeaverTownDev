
#include "BeaverTownDev.h"
#include "Trap.h"
#include "MainCharacter.h"

ATrap::ATrap()
{
	PrimaryActorTick.bCanEverTick = true;
<<<<<<< HEAD
	
}

// Called when the game starts or when spawned
void ATrap::BeginPlay()
{
	Super::BeginPlay();
	TrapActive = true;
=======
>>>>>>> Develop
}

void ATrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (TrapActive)
	{
		TrapTriggered();
	}
}

void ATrap::TrapTriggered()
{
	//If a TriggerVolume is enabled in editor, check for overlapping player. Spawns a falling rock above the player
	if (TrapTrigger)
	{
		AMainCharacter* MainCharacter = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
		if (TrapTrigger->IsOverlappingActor(MainCharacter))
		{
			UE_LOG(LogTemp, Warning, TEXT("Trap triggered!"))
			AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ObjectToSpawn, GetActorLocation() + GetActorForwardVector() *100.f, GetActorRotation());
			SpawnedActor->SetLifeSpan(Lifetime);
			UGameplayStatics::PlaySound2D(GetWorld(), TriggerSound, 1.f, 1.f, 0.f);
			TrapActive = false;
		}
	}
	
}

