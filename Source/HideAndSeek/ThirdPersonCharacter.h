// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "ThirdPersonCharacter.generated.h"

UCLASS(config = Game)
class HIDEANDSEEK_API AThirdPersonCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* MeshToChanged;
	
	class UStaticMesh* Asset;

public:
	// Sets default values for this character's properties
	AThirdPersonCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);
	// set if the player can move the object on which he is posing
	void CanMovesDirection();
	// block move
	void DontMovesDirection();

	

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	// Called every frame
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NewStatus")
	FString ReturnName;
	FString NameStatickMesh;
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NewStatus")
	bool canGetStatickMesh{ false };
	
	void CanGetTheStatcMeshView();
	void DontGetTheStatcMeshView();
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NewStatus")// bool var blcok a tick function "RotationPawn()", this function can rotation pawn(test UPROPERTY)
	bool canMove{ false };

	
	/* call this function in blueprint editor and Category makes a easy to find**/
	UFUNCTION(BlueprintCallable, Category = "Rotation staticmesh")
	void RotationPawn(float DeltaTime);
	UFUNCTION(BlueprintCallable, Category = "Line Tracer Get Name")
	void LineTracer(FString& ReturnNameOfStaticMesh);

	UFUNCTION(BlueprintCallable, Category = "Change Static Mesh")
	void GhangeStatic();
	
	// var controlling rotation value
	float cameraRotation{}, PawnRotation{};
		
	/** Returns CameraBoom subobject 
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
