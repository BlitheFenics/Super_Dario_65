// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HomingMissile.generated.h"


UCLASS()
class SUPER_DARIO_65_API AHomingMissile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHomingMissile();

	// ----------- to set up the collision component --------------- //
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		class UBoxComponent* CollisionBox;

	// ------------ the mesh component --------------- //
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MissileMesh")
		class UStaticMeshComponent* MissileMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		class UBoxComponent* BoxColider;

	void LockOn();

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
