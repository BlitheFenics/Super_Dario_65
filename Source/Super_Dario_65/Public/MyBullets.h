// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyBullets.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;


UCLASS(config=Game)
class SUPER_DARIO_65_API AMyBullets : public AActor
{
	GENERATED_BODY()
	
	// ------- defining the projectile movement component ------- //
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"));
	UProjectileMovementComponent* bulletMovement;

	// ---- this is defining the sphere collision component ------ //
	UPROPERTY(EditAnywhere, Category = Bullets)
	USphereComponent* bulletCollision;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bullets)
	UStaticMeshComponent* bulletMesh;

	// Sets default values for this actor's properties
	AMyBullets();

	UFUNCTION()
	void OnBoxComponentHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// ------- this returns the bullet collison subobject --------- //
	USphereComponent* GetBulletCollsion() const
	{
		return bulletCollision;
	}

	// -------- returns bullet movement subobject -------- //
	UProjectileMovementComponent* GetBulletMovement() const
	{
		return bulletMovement;
	}
};
