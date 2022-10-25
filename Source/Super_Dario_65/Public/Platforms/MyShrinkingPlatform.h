// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "MyShrinkingPlatform.generated.h"

UCLASS()
class SUPER_DARIO_65_API AMyShrinkingPlatform : public AActor
{

public:
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		class UStaticMeshComponent* ShrinkPlatform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		class UBoxComponent* BoxColider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		class UCurveFloat* CurveFloat;

	UFUNCTION()
		void OnBoxComponentHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnBoxComponentExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void OnShrinkProgress(float value);

	// Sets default values for this actor's properties
	AMyShrinkingPlatform();

private:
	FVector startScale;
	FVector targetScale;
	FTimeline ShrinkingTimeline;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
