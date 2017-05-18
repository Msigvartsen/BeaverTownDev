
#include "BeaverTownDev.h"
#include "MainCharacter.h"
#include "Interact.h"
#include "EnemyBase.h"
#include "MainGameInstance.h"
#include "EnemyAI.h"
#include "Chest.h"
#include "HealthPickups.h"

AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	PlayerCamera->SetupAttachment(CameraBoom);

	OverheadText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderComponent"));
	OverheadText->SetupAttachment(GetRootComponent());
	OverheadText->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	bCanJump = true;
	SetMaxWalkSpeed(WalkSpeed);
	GetCharacterMovement()->bNotifyApex = true;

	OverheadText->SetVisibility(false);
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Rotates character mesh towards the mouse cursor
	RotateToMousePosition(DeltaTime);
	
	FallingDamage();

	//Rotates Overhead text towards camera
	SetTextRotation(OverheadText);
	
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
	
	if (CanMelee)
	{
		CanMelee = false;
		GetWorld()->GetTimerManager().SetTimer(MeleeTimerHandle, this, &AMainCharacter::MeleeDelayEnd, AttackDelay);

		FHitResult HitResult;

		GetHitResultFromLineTrace(HitResult, MeleeRange);
		if (HitResult.GetActor())
		{

			if (HitResult.GetActor()->IsA(AEnemyAI::StaticClass()))
			{
				AEnemyAI* EnemyAIHit = Cast<AEnemyAI>(HitResult.GetActor());
				EnemyAIHit->SetTakeDamage(MeleeDamage);
			}

			if (HitResult.GetActor()->GetClass()->IsChildOf(AInteract::StaticClass()))
			{
				AInteract* InteractObject = Cast<AInteract>(HitResult.GetActor());

				if (InteractObject->GetCanBeDamaged())
				{
					InteractObject->OpenEvent();
				}
			}
		}
	}
}

void AMainCharacter::JumpPressed()
{	
	bCanJump = false;
	Jump();	
}

void AMainCharacter::JumpReleased()
{
	StopJumping();
}

void AMainCharacter::FallingDamage()
{
	if (!bFalling && GetCharacterMovement()->IsFalling() && GetVelocity().Z < 0.f)
	{
		bFalling = true;
		bCanTakeFallingDamage = true;
		StartJumpTime = GetWorld()->GetTimeSeconds();
	}
}

void AMainCharacter::Landed(const FHitResult & Hit)
{
	bCanJump = true;
	bFalling = false;
	EndJumpTime = GetWorld()->GetTimeSeconds();
	float SecondsInAir = EndJumpTime - StartJumpTime;
	if (SecondsInAir > 0.7f && GetVelocity().Z < 0.f)
	{
		SecondsInAir++;
		float HealthLost = FMath::Pow(SecondsInAir, 5.f);
		auto GameInstance = Cast<UMainGameInstance>(GetGameInstance());
		if (GameInstance && bCanTakeFallingDamage)
		{
			//GameInstance keeps track of player stats
			GameInstance->SetDamageTaken(HealthLost);
			bCanTakeFallingDamage = false;
		}
		UE_LOG(LogTemp, Warning, TEXT("TOOK %f FALLING DAMAGE!"), HealthLost);
		UE_LOG(LogTemp, Warning, TEXT("SECONDS IN AIR: %f! , END JUMP TIME %f, START JUMP TIME: %f"), SecondsInAir, EndJumpTime, StartJumpTime);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NO FALLING DAMAGE!"));
		bCanTakeFallingDamage = false;
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
			ChestRef = Cast<AChest>(InteractObject);
			if (HitResult.GetActor()->IsA(AHealthPickups::StaticClass()))
			{
				AHealthPickups* HealthPickup = Cast<AHealthPickups>(HitResult.GetActor());
				if (HealthPickup)
				{
					if (HealthPickup->GetCanHeal())
					{
						auto GameInstance = Cast<UMainGameInstance>(GetGameInstance());
						GameInstance->SetHealthIncrease(HealthPickup->HealTarget());
						HealthPickup->SetHealUsed();
					}
					
	
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
	
	if (!IsPushingObject)
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
		
		FRotator NewRotation = FMath::RInterpConstantTo(GetActorRotation(), RotatedMouseVector.Rotation(), DeltaTime, TurnInterpolationSpeed);
	
		GetWorld()->GetFirstPlayerController()->SetControlRotation(NewRotation);
	}
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

void AMainCharacter::SetIsPushingObject(bool IsPushing)
{
	IsPushingObject = IsPushing;
	UE_LOG(LogTemp,Warning,TEXT("Locks camera rotation!"))
}


void AMainCharacter::SetMaxWalkSpeed(float MovementSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;
}

USoundBase* AMainCharacter::GetHurtSound()
{
	return HurtSound;
}

void AMainCharacter::SetOverheadText()
{
	LootText = ChestRef->GetLootText();
	OverheadText->SetText(LootText);
	OverheadText->SetVisibility(true);
	IsTextVisible = true;
	UE_LOG(LogTemp, Warning, TEXT("Setting overhead Text!"))
	SetVisibilityOverheadText();
}

void AMainCharacter::SetTextRotation(UTextRenderComponent* TextRenderComp)
{
	// rotates text so it will face the camera
	FVector TextLocation = TextRenderComp->GetComponentLocation();
	FVector CameraLocation = PlayerCamera->GetComponentLocation();
	FVector End = CameraLocation - TextLocation;


	FRotator Rotation = FRotationMatrix::MakeFromX(End).Rotator();
	TextRenderComp->SetWorldRotation(FRotator(Rotation.Pitch, Rotation.Yaw, 0));
}

void AMainCharacter::SetVisibilityOverheadText()
{
	if (IsTextVisible)
	{
		
		IsTextVisible = false;
		if (GetWorld())
		{
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMainCharacter::TimerEnd, OverheadTextDespawnTime);
		}	
	}
}

void AMainCharacter::TimerEnd()
{
	OverheadText->SetVisibility(false);
	UE_LOG(LogTemp,Warning,TEXT("Timer ended for text!"))
		if (GetWorld())
		{
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		}
	
}

void AMainCharacter::MeleeDelayEnd()
{
	if (GetWorld())
	{
		CanMelee = true;
		GetWorld()->GetTimerManager().ClearTimer(MeleeTimerHandle);
	}
}