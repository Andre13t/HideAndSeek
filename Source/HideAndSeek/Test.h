// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Test.generated.h"

UCLASS()
class HIDEANDSEEK_API ATest : public AActor
{
	GENERATED_BODY()
	
public:	
	// add root component
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ActorRootSceneComponent;
	// Sets default values for this actor's properties
	ATest();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// create a mesh in this actor
	//UPROPERTY(VisibleAnywhere)
	//UStaticMeshComponent* Supermesh;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
