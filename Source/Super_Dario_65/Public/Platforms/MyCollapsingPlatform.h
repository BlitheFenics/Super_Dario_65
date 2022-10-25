// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyCollapsingPlatform.generated.h"

UCLASS()
class SUPER_DARIO_65_API AMyCollapsingPlatform : public AActor
{
public:
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		class UStaticMeshComponent* CollapsingPlatform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		class UBoxComponent* BoxColider;

	UFUNCTION()
		void OnBoxComponentHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnBoxComponentExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	float time;
	bool hit;

	FVector originalPosition;
	FRotator originalRotation;

	// Sets default values for this actor's properties
	AMyCollapsingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
