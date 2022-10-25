// Fill out your copyright notice in the Description page of Project Settings.


#include "Platforms/MyCollapsingPlatform.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Characters/DarioBase.h"


// Sets default values
AMyCollapsingPlatform::AMyCollapsingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollapsingPlatform = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CollapsingPlatform"));
	CollapsingPlatform->SetupAttachment(RootComponent);
	BoxColider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxColider"));
	BoxColider->SetupAttachment(CollapsingPlatform);

	BoxColider->OnComponentBeginOverlap.AddDynamic(this, &AMyCollapsingPlatform::OnBoxComponentHit);
	BoxColider->OnComponentEndOverlap.AddDynamic(this, &AMyCollapsingPlatform::OnBoxComponentExit);

	hit = false;



}

// Called when the game starts or when spawned
void AMyCollapsingPlatform::BeginPlay()
{
	Super::BeginPlay();
	originalPosition = CollapsingPlatform->GetComponentLocation();
	originalRotation = CollapsingPlatform->GetComponentRotation();

}

// Called every frame
void AMyCollapsingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (hit)
	{
		time += DeltaTime;
		if (time > 10.0f)
		{
			CollapsingPlatform->SetSimulatePhysics(false);

			FVector location = FMath::VInterpTo(CollapsingPlatform->GetComponentLocation(), originalPosition, DeltaTime, 4.0f);
			FRotator rotation = FMath::RInterpTo(CollapsingPlatform->GetComponentRotation(), originalRotation, DeltaTime, 4.0f);
			CollapsingPlatform->SetWorldLocation(location);
			CollapsingPlatform->SetWorldRotation(rotation);

			if (rotation.Equals(originalRotation, 2.0f) && location.Equals(originalPosition, 2.0f))
			{
				hit = false;
				time = 0;
			}
		}

	}

}

void AMyCollapsingPlatform::OnBoxComponentHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ADarioBase>(OtherActor))
	{
		hit = true;


		CollapsingPlatform->SetSimulatePhysics(true);
	}
}

void AMyCollapsingPlatform::OnBoxComponentExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}


