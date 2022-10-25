// Fill out your copyright notice in the Description page of Project Settings.


#include "HomingMissile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"


// Sets default values
AHomingMissile::AHomingMissile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MissileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Missle Mesh"));
	//MissileMesh->SetupAttachment(RootComponent);
	//MissileMesh->rotation

	BoxColider = CreateAbstractDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	BoxColider->SetupAttachment(RootComponent);
	BoxColider->OnComponentBeginOverlap.AddDynamic(this, &AHomingMissile::OnOverlapBegin);

}

void AHomingMissile::LockOn()
{
	ACharacter* const dario = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FVector location = dario->GetActorLocation() - GetActorLocation();
	FRotator rotation = location.ToOrientationRotator();
	//SetActorRotation(FQuat::Slerp(GetActorQuat(), FQuat::MakeFromEuler(location), .001f));

	SetActorRotation(FMath::RInterpTo(GetActorRotation(), rotation, .01f, .01f));

	
}

void AHomingMissile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		Destroy();
	}
}

// Called when the game starts or when spawned
void AHomingMissile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHomingMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	LockOn();

}

