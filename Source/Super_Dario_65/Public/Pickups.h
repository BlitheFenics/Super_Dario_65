// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickups.generated.h"

UCLASS()
class SUPER_DARIO_65_API APickups : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	APickups();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		class UStaticMeshComponent* rodCollect;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DarioRef")
		class ADarioBase* DarioRef;


	float amplitude;
	FVector oriLoc;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
