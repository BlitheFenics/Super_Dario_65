// Fill out your copyright notice in the Description page of Project Settings.


#include "Platforms/MySplineTrack.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SplineComponent.h"
#include "Components/BoxComponent.h"
#include "Characters/DarioBase.h"


// Sets default values
AMySplineTrack::AMySplineTrack()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SceneRoot->SetupAttachment(RootComponent);

	Platform = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform"));
	Platform->SetupAttachment(SceneRoot);

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	Spline->SetupAttachment(SceneRoot);

	BoxColider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxColider"));
	BoxColider->SetupAttachment(Platform);

}

void AMySplineTrack::OnTimelineProgress(float value)
{
	const float distance = Spline->GetSplineLength();
	const float currentDistance = distance * value;
	const FVector location = Spline->GetLocationAtDistanceAlongSpline(currentDistance, ESplineCoordinateSpace::World);
	const FRotator rotator = Spline->GetRotationAtDistanceAlongSpline(currentDistance, ESplineCoordinateSpace::World);

	Platform->SetWorldLocation(location);
	Platform->SetWorldRotation(FRotator(0.0f, rotator.Yaw, 0.0f));

	//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Red, FString::Printf(TEXT("%f"), value));
}

void AMySplineTrack::OnTimelineCompleted()
{
	FOnTimelineEventStatic timelineComplete;
	timelineComplete.BindUFunction(this, FName("OnTimelineReverse"));

	FOnTimelineFloat TimelineFloat;
	TimelineFloat.BindUFunction(this, FName("OnTimelineProgress"));
	Timeline.AddInterpFloat(CurveFloat, TimelineFloat);
	Timeline.SetLooping(false);
	Timeline.Reverse();
	Timeline.SetTimelineFinishedFunc(timelineComplete);

}

void AMySplineTrack::OnTimelineReverse()
{

	FOnTimelineFloat TimelineFloat;
	TimelineFloat.BindUFunction(this, FName("OnTimelineProgress"));

	FOnTimelineEventStatic TimelineFinished;
	TimelineFinished.BindUFunction(this, FName("OnTimelineCompleted"));
	Timeline.AddInterpFloat(CurveFloat, TimelineFloat);
	Timeline.SetLooping(false);
	Timeline.Play();
	Timeline.SetTimelineFinishedFunc(TimelineFinished);
}


// Called when the game starts or when spawned
void AMySplineTrack::BeginPlay()
{
	Super::BeginPlay();
	//if (Cast<APlat_PickCharacter>(OtherActor))
	//{


	FOnTimelineFloat TimelineFloat;
	TimelineFloat.BindUFunction(this, FName("OnTimelineProgress"));

	FOnTimelineEventStatic TimelineFinished;
	TimelineFinished.BindUFunction(this, FName("OnTimelineCompleted"));
	Timeline.AddInterpFloat(CurveFloat, TimelineFloat);
	Timeline.SetLooping(false);
	Timeline.Play();
	Timeline.SetTimelineFinishedFunc(TimelineFinished);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Red, "wowie");
//}

}

// Called every frame
void AMySplineTrack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Timeline.TickTimeline(DeltaTime);

}

