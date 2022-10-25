// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"

#include "MySplineTrack.generated.h"

UCLASS()
class SUPER_DARIO_65_API AMySplineTrack : public AActor
{
public:
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SplineInfo)
		class USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SplineInfo)
		class UStaticMeshComponent* Platform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SplineInfo)
		class USplineComponent* Spline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SplineInfo)
		class UBoxComponent* BoxColider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SplineInfo)
		class UCurveFloat* CurveFloat;

	UFUNCTION()
		void OnTimelineProgress(float value);

	UFUNCTION()
		void OnTimelineCompleted();

	UFUNCTION()
		void OnTimelineReverse();

	FTimeline Timeline;




	// Sets default values for this actor's properties
	AMySplineTrack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
