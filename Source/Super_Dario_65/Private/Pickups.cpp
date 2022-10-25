// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Characters/DarioBase.h"

// Sets default values
APickups::APickups()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rodCollect = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("Rod Pickup"));
	rodCollect->SetupAttachment(RootComponent);

}



// Called when the game starts or when spawned
void APickups::BeginPlay()
{
	Super::BeginPlay();

	amplitude = 0.0f;
	oriLoc = GetActorLocation();


}

// Called every frame
void APickups::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	amplitude += 3.0f * DeltaTime;

	const FVector offSet = FVector(0.0f, 0.0f, 20.0f * FMath::Sin(amplitude));
	rodCollect->SetWorldLocation(oriLoc + offSet);
	rodCollect->AddLocalRotation(FQuat::MakeFromEuler(FVector(0.0f, 0.0f, 20.0f * DeltaTime)));

}

