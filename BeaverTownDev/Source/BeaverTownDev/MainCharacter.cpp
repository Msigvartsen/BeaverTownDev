
#include "BeaverTownDev.h"
#include "MainCharacter.h"
#include "Interact.h"
#include "EnemyBase.h"
#include "MainGameInstance.h"
#include "HealthPickups.h"

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
	bCanJump = true;
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateToMousePosition(DeltaTime);
	
}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("MoveX", this, &AMainCharacter::MoveX);
	InputComponent->BindAxis("MoveY", this, &AMainCharacter::MoveY);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::JumpPressed);
	InputComponent->BindAction("Jump", IE_Released, this, &AMainCharacter::JumpReleased);
	InputComponent->BindAction("Melee", IE_Pressed, this, &AMainCharacter::Melee);
	InputComponent->BindAction("Interact", IE_Pressed, this, &AMainCharacter::Interact);
	InputComponent->BindAction("Interact", IE_Released, this, &AMainCharacter::InteractReleased);
	
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

	GetHitResultFromLineTrace(HitResult, MeleeRange);
	if (HitResult.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("Line Trace hit: %s"), *HitResult.Actor->GetClass()->GetName())

		if (HitResult.GetActor()->IsA(AEnemyBase::StaticClass()))
		{
			AEnemyBase* EnemyHit = Cast<AEnemyBase>(HitResult.GetActor());
			EnemyHit->RemoveHealth(MeleeDamage);
		}
		else if (HitResult.GetActor()->GetClass()->IsChildOf(AInteract::StaticClass()))
		{
			AInteract* InteractObject = Cast<AInteract>(HitResult.GetActor());
			
			if (InteractObject->GetCanBeDamaged())
			{
				InteractObject->OpenEvent();
			}
		}
	}
}

void AMainCharacter::JumpPressed()
{	
	UE_LOG(LogTemp, Warning, TEXT("JUMPING! %d"), bCanJump);
	bCanJump = false;
	Jump();	
}

void AMainCharacter::JumpReleased()
{
	StopJumping();
}

void AMainCharacter::Landed(const FHitResult & Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("LANDED!"));
	bCanJump = true;
	EndJumpTime = GetWorld()->GetTimeSeconds();
	float SecondsInAir = EndJumpTime - StartJumpTime;
	if (SecondsInAir > 1.f)
	{
		float HealthLost = SecondsInAir * 10;
		auto GameInstance = Cast<UMainGameInstance>(GetGameInstance());
		if (GameInstance)
		{
			//GameInstance keeps track of player stats
			GameInstance->SetDamageTaken(HealthLost);
		}
		UE_LOG(LogTemp, Warning, TEXT("TOOK %f FALLING DAMAGE!"), SecondsInAir);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NO FALLING DAMAGE!"));
	}
}

void AMainCharacter::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PrevMovementMode, PreviousCustomMode);
	if (GetCharacterMovement()->IsFalling())
	{
		StartJumpTime = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("FALLING!"));
	}
}

void AMainCharacter::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("Interacting!"));

	bIsInteractActive = true;
	
	FHitResult HitResult;
	GetHitResultFromLineTrace(HitResult, InteractReach);

	// Opens chest if hit
	if (HitResult.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("Line Trace hit: %s"), *HitResult.Actor->GetName())

		if (HitResult.GetActor()->GetClass()->IsChildOf(AInteract::StaticClass()))
		{
			AInteract* InteractObject = Cast<AInteract>(HitResult.GetActor());
			if (HitResult.GetActor()->IsA(AHealthPickups::StaticClass()))
			{
				AHealthPickups* HealthPickup = Cast<AHealthPickups>(HitResult.GetActor());
				if (HealthPickup)
				{
					auto GameInstance = Cast<UMainGameInstance>(GetGameInstance());
					GameInstance->SetHealth(HealthPickup->HealTarget());
	
				}
			}
			float PlayerAngle = GetActorRotation().Yaw;
			float MinAngle = InteractObject->GetActorForwardVector().Rotation().Yaw + InteractObject->GetMinOpenAngle();
			float MaxAngle = InteractObject->GetActorForwardVector().Rotation().Yaw + InteractObject->GetMaxOpenAngle();

			if (InteractObject->GetOnlyInteractFromAngle())
			{
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
			else if(InteractObject->GetCanBeDamaged() == false)
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
	FRotator NewRotation = FMath::RInterpConstantTo(GetActorRotation(), RotatedMouseVector.Rotation(),DeltaTime,500.f);
	GetWorld()->GetFirstPlayerController()->SetControlRotation(NewRotation);
}



void AMainCharacter::GetHitResultFromLineTrace(FHitResult &HitResult,float Reach)
{
	FVector StartTrace = GetActorLocation();
	FVector EndTrace = StartTrace + (GetActorRotation().Vector() * Reach);
	EndTrace.Z -= 25.f;
	StartTrace.Z -= 25.f;

	// Draws a red line that represents the line trace
	DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor(0, 255, 0), false, .3f, 0, 10.f);

	// Line trace from character mesh to get World Dynamic object
	GetWorld()->LineTraceSingleByObjectType(
		HitResult,
		StartTrace,
		EndTrace,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldDynamic),
		FCollisionQueryParams(FName(TEXT("")), false, Cast<AActor>(this))
		);
}


void AMainCharacter::SetIsInteractActive(bool Status)
{
	bIsInteractActive = Status;
}

bool AMainCharacter::GetIsInteractActive() const
{
	return bIsInteractActive;
}

