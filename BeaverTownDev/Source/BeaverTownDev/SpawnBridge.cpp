
#include "BeaverTownDev.h"
#include "MainCharacter.h"
#include "MainGameInstance.h"
#include "SpawnBridge.h"


ASpawnBridge::ASpawnBridge()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ASpawnBridge::BeginPlay()
{
	Super::BeginPlay();
	
	BridgeMesh = FindComponentByClass<UStaticMeshComponent>();
	BridgeMesh->SetVisibility(false, true);
	this->SetActorEnableCollision(false);
	
}

void ASpawnBridge::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PlayerCollectedWood = Cast<UMainGameInstance>(GetGameInstance())->GetWoodParts();
	if (PlayerCollectedWood == BridgeIndex)
	{
		BuildBridge();
	}
	
}

void ASpawnBridge::BuildBridge()
{
	if (!BridgeTrigger) { return; }
	AMainCharacter* MainCharacter = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	
	if (BridgeTrigger->IsOverlappingActor(MainCharacter))
	{
		BridgeMesh->SetVisibility(true, true);
		this->SetActorEnableCollision(true);
		
	}
}