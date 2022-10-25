// Fill out your copyright notice in the Description page of Project Settings.


#include "Platforms/MyShrinkingPlatform.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Characters/DarioBase.h"

// Sets default values
AMyShrinkingPlatform::AMyShrinkingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShrinkPlatform = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShrinkingPlatform"));
	ShrinkPlatform->SetupAttachment(RootComponent);
	BoxColider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxColider"));
	BoxColider->SetupAttachment(ShrinkPlatform);

	BoxColider->OnComponentBeginOverlap.AddDynamic(this, &AMyShrinkingPlatform::OnBoxComponentHit);
	BoxColider->OnComponentEndOverlap.AddDynamic(this, &AMyShrinkingPlatform::OnBoxComponentExit);

	//startScale = FVector(1.0, 1.0, 0.14);
 /*this->GeGetActorScale3D();*/
	targetScale = FVector(0, 0, 0);

}

// Called when the game starts or when spawned
void AMyShrinkingPlatform::BeginPlay()
{
	Super::BeginPlay();

	startScale = ShrinkPlatform->GetComponentScale();

}

// Called every frame
void AMyShrinkingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ShrinkingTimeline.TickTimeline(DeltaTime);
	
	FVector scaleXY = ShrinkPlatform->GetComponentScale();
	scaleXY.Z = 0.0f;
	float mag = scaleXY.Size();

	if (mag == 0.0f)
	{
		this->SetActorEnableCollision(false);
	}
	else
	{
		this->SetActorEnableCollision(true);

	}

	//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Red, "wowie");

}


void AMyShrinkingPlatform::OnBoxComponentHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ADarioBase>(OtherActor))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, "wowie");

		FOnTimelineFloat TimelineFloat;
		TimelineFloat.BindUFunction(this, FName("OnShrinkProgress"));
		ShrinkingTimeline.AddInterpFloat(CurveFloat, TimelineFloat);
		ShrinkingTimeline.SetLooping(true);
		ShrinkingTimeline.Play();
	}

}

void AMyShrinkingPlatform::OnBoxComponentExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ADarioBase>(OtherActor))
	{
		ShrinkingTimeline.SetLooping(false);

	}
}

void AMyShrinkingPlatform::OnShrinkProgress(float value)
{
	FVector newScale = FMath::Lerp(startScale, targetScale, value);
	ShrinkPlatform->SetWorldScale3D(newScale);
	BoxColider->SetWorldScale3D(newScale);

	FVector scaleXY = ShrinkPlatform->GetComponentScale();
	scaleXY.Z = 0.0f;
	float mag = scaleXY.Size();

	if (mag == 0.0f)
	{
		this->SetActorEnableCollision(false);
	}
}


