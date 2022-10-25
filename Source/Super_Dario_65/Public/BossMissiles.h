// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossMissiles.generated.h"

UCLASS()
class SUPER_DARIO_65_API ABossMissiles : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABossMissiles(const FObjectInitializer& ObjectInit);


private:
	// ------------ the target variables ---------------- //
	bool hasTargetPosition;
	bool hasNoTarget;
	class AActor* target;

	// ----------------- delay, for the missiles to shoot upwards initially  ------------ //
	float delayTimer;
	bool hasFinishedDelay;

	// -------------- actor lifetime variables ------------ //
	float lifetimeCountdown;
	bool canBeDestroyed;
	void Explode();

	// ------------------ event to detect when an actor overlaps with the missiles --------------- //
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// ----------- refernce the player in the world ---------- //
	class ADarioBase* playerInWorld;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// ---------- for a short delay ------------ //
	void Delay(float deltaTime);

	// ----------- find the target ----------- //
	void FindDario();
	void UpdateTarget();

	// ----------- to set up the collision component --------------- //
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		class UBoxComponent* CollisionBox;

	// ------------ the mesh component --------------- //
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MissileMesh")
		class UStaticMeshComponent* MissileMesh;

	// ---------------------- projectile movement component ----------- //
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
		class UProjectileMovementComponent* ProjectileMovement;


	// ---------- add the explosion particle variables here ----------------- //




	// ---------- add the explosion sound variables here ----------------- //


};
