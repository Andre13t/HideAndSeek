// Fill out your copyright notice in the Description page of Project Settings.


#include "Test.h"


// Sets default values
ATest::ATest()
{
	// 
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// create root component 
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	//UStaticMeshComponent* OurStatic = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("AnotherStaticMesh"));
	ActorRootSceneComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ActorRootComponet"));
	
	//Supermesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MY SUPER MESH"));
	// create a Sub-object from cpp file
	
	//Supermesh->SetupAttachment(RootComponent);


	ActorRootSceneComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATest::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

