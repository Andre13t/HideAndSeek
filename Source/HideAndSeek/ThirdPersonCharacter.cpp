// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
//#include "Components/StaticMeshComponent.h"
//#include "Engine/StaticMesh.h"
//#include "UObject/ConstructorHelpers.h"

// Sets default values
AThirdPersonCharacter::AThirdPersonCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm	

	// create mesh
	MeshToChanged = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshToChanged"));
	MeshToChanged->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/Props/SM_Prop_Hydrant_01.SM_Prop_Hydrant_01'"));
	Asset = MeshAsset.Object;
}

// Called when the game starts or when spawned
void AThirdPersonCharacter::BeginPlay()
{
	Super::BeginPlay();
	

	
	//Asset->GetName();
	MeshToChanged->SetStaticMesh(Asset);
	/*if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, FString::Printf(TEXT("Component name: %s"),
			Asset->GetName()));
	}*/
	
}

// Called every frame
void AThirdPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (canGetStatickMesh)
	{
		

	}
	

	// rotation pawn
	if (canMove)
	{
		int32 a = 2;
		RotationPawn(DeltaTime,a);
	}
}

// Called to bind functionality to input
void AThirdPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("CanMoveObject", IE_Pressed, this, &AThirdPersonCharacter::CanMovesDirection);
	PlayerInputComponent->BindAction("CanMoveObject", IE_Released, this, &AThirdPersonCharacter::DontMovesDirection);

	PlayerInputComponent->BindAxis("MoveForward", this, &AThirdPersonCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AThirdPersonCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	// set up "switch the body"
	PlayerInputComponent->BindAction("SwitchTheBody", IE_Pressed, this, &AThirdPersonCharacter::CanGetTheStatcMeshView);
	PlayerInputComponent->BindAction("SwitchTheBody", IE_Released, this, &AThirdPersonCharacter::DontGetTheStatcMeshView);
}

void AThirdPersonCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AThirdPersonCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AThirdPersonCharacter::CanMovesDirection()
{
	// set inicial value of camera rotation and pawn
	PawnRotation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorRotation().Yaw;
	cameraRotation = FollowCamera->GetComponentRotation().Yaw;
	// set if tick can rotation pawn
	canMove = true;
}

void AThirdPersonCharacter::DontMovesDirection()
{
	canMove = false;// set if tick can rotation pawn
}

void AThirdPersonCharacter::RotationPawn(float DeltaTime, int32& asd)
{
	// calculation to determine how much the spawn will rotate according to the camera
	float GetAddYawValue = (PawnRotation + ((-1) * (cameraRotation - FollowCamera->GetComponentRotation().Yaw)));
	// using delta time on value to keep same value independent of frame hate
	
	//GetCapsuleComponent()->SetWorldRotation(FRotator(0, GetAddYawValue, 0));
	asd = 10;
	// for avoid flic rotation whe the value is equal
	if (PawnRotation != GetAddYawValue)
	{
		GetAddYawValue -= GetAddYawValue * DeltaTime;
		// set up new rotation of pawn
		GetCapsuleComponent()->SetWorldRotation(FRotator(0, GetAddYawValue, 0));
	}
}

void AThirdPersonCharacter::CanGetTheStatcMeshView()
{
	canGetStatickMesh = true;

}

void AThirdPersonCharacter::DontGetTheStatcMeshView()
{
	canGetStatickMesh = false;
}

void AThirdPersonCharacter::LineTracer(FString& ReturnNameOfStaticMesh)
{
	FHitResult OutHit;
	//FVector Start = FollowCamera->GetComponentLocation();
	FVector Start = GetCapsuleComponent()->GetComponentLocation();
	FVector ForwardVector = FollowCamera->GetForwardVector();
	FVector End = (Start + (ForwardVector * 500.0f));

	FCollisionQueryParams CollisionParams;

	//DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);

	bool isHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams);
	if (isHit)
		if (OutHit.bBlockingHit)
			if (GEngine)
			{
				FString porra = OutHit.GetActor()->GetName();
				ReturnNameOfStaticMesh = porra;
				////ReturnNameOfStaticMesh =  *OutHit.GetActor()->GetName();
				////GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Name: %s", *OutHit.GetActor()->GetComponents())));
				//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Name: %s"),
				//	*OutHit.GetActor()->GetName()));
			}
}

