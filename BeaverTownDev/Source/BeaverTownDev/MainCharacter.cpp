
#include "BeaverTownDev.h"
#include "MainCharacter.h"


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
	FHitResult Hit;
	bool HitResult = GetWorld()->LineTraceSingleByObjectType(Hit, GetActorLocation(), GetActorLocation() + 10.f,ECC_WorldStatic);
	FVector StartTrace = GetActorLocation();
	FVector EndTrace = StartTrace + (GetActorRotation().Vector() * 500.f);
	DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor(255, 0, 0), true, -1.f, 0.f,10.f);
	
	if (HitResult)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found HIT"));
	}
}

void AMainCharacter::Dodge()
{
	if (Stamina > 40)
	{
		FVector DodgeDirection(0, 0, 0);
		DodgeDirection += FVector::ForwardVector * InputComponent->GetAxisValue("MoveX");
		DodgeDirection += FVector::RightVector * InputComponent->GetAxisValue("MoveY");
		DodgeDirection.Normalize();
		LaunchCharacter((DodgeDirection*DodgeSpeed), true, false);
		Stamina -= 40.f;
	}
}

void AMainCharacter::RotateToMousePosition(float DeltaTime)
{
	//Find Position to Mouse, and store inside Vector. Find Viewport Center and calculate mouse position from center. Character rotates after mouse.
	float X, Y;
	GetWorld()->GetFirstPlayerController()->GetMousePosition(X, Y);
	FVector2D MouseLocation = FVector2D(X, Y);
	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	const FVector2D  ViewportCenter = FVector2D(ViewportSize.X / 2, ViewportSize.Y / 2);
	FVector2D MouseDirection = MouseLocation - ViewportCenter;
	FVector RotationAngle = FVector(MouseDirection.X, MouseDirection.Y, 0);

	//Rotates smoothly towards mouse cursor
	
	FRotator NewRotation = FMath::RInterpConstantTo(GetActorRotation(),RotationAngle.Rotation(),DeltaTime,340.f);
	GetWorld()->GetFirstPlayerController()->SetControlRotation(NewRotation);
}

float AMainCharacter::GetHealthPercent()
{
	return (Health / MaxHealth);
}

float AMainCharacter::GetStaminaPercent()
{
	return (Stamina / MaxStamina);
}