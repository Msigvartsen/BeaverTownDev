
#include "BeaverTownDev.h"
#include "MainCharacter.h"
#include "Interact.h"
#include "EnemyBase.h"
#include "ComplexProjectile.h"
#include "Projectile.h"

AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	PlayerCamera->SetupAttachment(CameraBoom);
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateToMousePosition(DeltaTime);

	if (Stamina < 100)
	{
		Stamina += StaminaRegeneration * DeltaTime;
	}
}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("MoveX", this, &AMainCharacter::MoveX);
	InputComponent->BindAxis("MoveY", this, &AMainCharacter::MoveY);
	InputComponent->BindAction("Dodge", IE_Pressed, this, &AMainCharacter::Dodge);
	InputComponent->BindAction("Melee", IE_Pressed, this, &AMainCharacter::Melee);
	InputComponent->BindAction("Shoot", IE_Pressed, this, &AMainCharacter::Shoot);
	InputComponent->BindAction("Interact", IE_Pressed, this, &AMainCharacter::Interact);
	InputComponent->BindAction("Interact", IE_Released, this, &AMainCharacter::InteractReleased);
	InputComponent->BindAction("Inventory", IE_Pressed, this, &AMainCharacter::ShowInventory);
	InputComponent->BindAction("Inventory", IE_Released, this, &AMainCharacter::HideInventory);
	InputComponent->BindAction("WeaponOne", IE_Pressed, this, &AMainCharacter::WeaponOne);
	InputComponent->BindAction("WeaponTwo", IE_Pressed, this, &AMainCharacter::WeaponTwo);
	InputComponent->BindAction("Heal", IE_Pressed, this, &AMainCharacter::Heal);
}

void AMainCharacter::MoveX(float value)
{
	AddMovementInput(FVector::ForwardVector, value);
}

void AMainCharacter::MoveY(float value)
{
	AddMovementInput(FVector::RightVector, value);
}

void AMainCharacter::Melee()
{
	UE_LOG(LogTemp, Warning, TEXT("Melee!"));
	FHitResult HitResult;
	
	FVector StartTrace = GetActorLocation();
	FVector EndTrace = StartTrace + (GetActorRotation().Vector() * MeleeRange);
	GetWorld()->LineTraceSingleByObjectType(
		HitResult,
		StartTrace,
		EndTrace,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldDynamic),
		FCollisionQueryParams(FName(TEXT("")), false, Cast<AActor>(this)));

	DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor(255, 0, 0), false, 1.f, 0.f,10.f);
	EndTrace.Z = 25.f;
	StartTrace.Z = 25.f;
	if (HitResult.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("Line Trace hit: %s"), *HitResult.Actor->GetClass()->GetName())

			if (HitResult.GetActor()->IsA(AEnemyBase::StaticClass()))
			{
				AEnemyBase* EnemyHit = Cast<AEnemyBase>(HitResult.GetActor());
				EnemyHit->RemoveHealth(MeleeDamage);
			}
	}
}

void AMainCharacter::Dodge()
{
	if (Stamina > 30)
	{
		FVector DodgeDirection(0, 0, 0);
		DodgeDirection += FVector::ForwardVector * InputComponent->GetAxisValue("MoveX");
		DodgeDirection += FVector::RightVector * InputComponent->GetAxisValue("MoveY");
		DodgeDirection.Normalize();
		LaunchCharacter((DodgeDirection*DodgeSpeed), true, false);
		Stamina -= 40.f;
	}
}

void AMainCharacter::Shoot()
{
	UE_LOG(LogTemp, Warning, TEXT("Shooting!"));

	switch (WeaponOfChoice)
	{
	case 1:
		ThrowNut();
		break;
	case 2:
		ThrowRock();
		break;
	default:
		UE_LOG(LogTemp,Warning,TEXT("Error choosing and shooting"))
	}	
}

void AMainCharacter::Heal()
{
	Health += HealingPotion;
}

void AMainCharacter::WeaponOne()
{
	WeaponOfChoice = 1;
}
void AMainCharacter::WeaponTwo()
{
	WeaponOfChoice = 2;
}

void AMainCharacter::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("Interacting!"));

	bIsInteractActive = true;
	
	FHitResult HitResult;
	GetHitResultFromLineTrace(HitResult);
	// Opens chest if hit
	if (HitResult.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("Line Trace hit: %s"), *HitResult.Actor->GetName())

		if (HitResult.GetActor()->GetClass()->IsChildOf(AInteract::StaticClass()))
		{
			AInteract* InteractObject = Cast<AInteract>(HitResult.GetActor());

			float PlayerAngle = GetActorRotation().Yaw;
			float MinAngle = InteractObject->GetActorForwardVector().Rotation().Yaw + InteractObject->GetMinOpenAngle();
			float MaxAngle = InteractObject->GetActorForwardVector().Rotation().Yaw + InteractObject->GetMaxOpenAngle();

			if (PlayerAngle > MinAngle && PlayerAngle < MaxAngle)
			{
				if (InteractObject->GetIsOpenEvent())
				{
					InteractObject->CloseEvent();
				}
				else
				{
					InteractObject->OpenEvent();
				}
			}
		}
	}
}

void AMainCharacter::InteractReleased()
{
	UE_LOG(LogTemp, Warning, TEXT("InteractReleased"))
	bIsInteractActive = false;
}

// Find Viewport Center and mouse 2D position, then get rotation vector based on viewport center. 
// Character rotates towards mouse position.
void AMainCharacter::RotateToMousePosition(float DeltaTime)
{
	/// get viewport center
	FVector2D ViewportSize;
	FVector2D  ViewportCenter;
	GetWorld()->GetGameViewport()->GetViewportSize(ViewportSize);
	ViewportCenter = ViewportSize / 2;

	/// get mouse position
	float X, Y;
	GetWorld()->GetFirstPlayerController()->GetMousePosition(X, Y);
	FVector2D MousePosition = FVector2D(X, Y);

	/// Get rotation vector
	FVector2D MouseDirection = MousePosition - ViewportCenter;
	MouseDirection.Normalize();
	FVector MouseDirection3D = FVector(MouseDirection.X, MouseDirection.Y, 0);

	/// Fixes rotation offset
	FRotator MyRotator = FRotator(0, 90, 0);
	FRotationMatrix MyRotationMatrix(MyRotator);
	FVector RotatedMouseVector = MyRotationMatrix.TransformVector(MouseDirection3D);

	/// Rotates smoothly towards mouse cursor
	FRotator NewRotation = FMath::RInterpConstantTo(GetActorRotation(), RotatedMouseVector.Rotation(),DeltaTime,400.f);
	GetWorld()->GetFirstPlayerController()->SetControlRotation(NewRotation);
	
}



void AMainCharacter::GetHitResultFromLineTrace(FHitResult &HitResult)
{
	FVector StartTrace = GetActorLocation();
	FVector EndTrace = StartTrace + (GetActorRotation().Vector() * InteractReach);
	EndTrace.Z -= 25.f;
	StartTrace.Z -= 25.f;
	HitResult;

	// Draws a red line that represents the line trace
	DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor(0, 255, 0), true, -1.f, 0, 10.f);

	// Line trace from character mesh to get World Dynamic object
	GetWorld()->LineTraceSingleByObjectType(
		HitResult,
		StartTrace,
		EndTrace,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldDynamic),
		FCollisionQueryParams(FName(TEXT("")), false, Cast<AActor>(this))
		);
}

void AMainCharacter::ThrowRock()
{
	FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 100.f;
	if (ComplexProjectileBlueprint)
	{
		AComplexProjectile* Projectile = GetWorld()->SpawnActor<AComplexProjectile>(ComplexProjectileBlueprint, SpawnLocation, GetActorRotation());
		Projectile->Shoot(1000.f);

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No projectile found!"));
	}
}

void AMainCharacter::ThrowNut()
{
	if (GetWorld())
	{
		FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 100.f;
		GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,SpawnLocation, GetActorRotation());
	}
}

void AMainCharacter::ShowInventory()
{
	IsInventoryVisible = true;
}

void AMainCharacter::HideInventory()
{
	IsInventoryVisible = false;
}

float AMainCharacter::GetHealthPercent() const
{
	return (Health / MaxHealth);
}

void AMainCharacter::SetHealth(float DamageTaken)
{
	Health -= DamageTaken;
}

float AMainCharacter::GetStaminaPercent() const
{
	return (Stamina / MaxStamina);
}

void AMainCharacter::SetCollectedMinerals()
{
	CollectedMinerals++;
}
int AMainCharacter::GetCollectedMinerals() const
{
	return CollectedMinerals;
}

void AMainCharacter::SetIsInteractActive(bool Status)
{
	bIsInteractActive = Status;
}

bool AMainCharacter::GetIsInteractActive() const
{
	return bIsInteractActive;
}