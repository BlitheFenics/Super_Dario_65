// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ReactorBoss.generated.h"

UCLASS()
class SUPER_DARIO_65_API AReactorBoss : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AReactorBoss(const FObjectInitializer& objInit);

private:
	FTimerHandle missleTimerHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ------- spawning the missiles ---------- //
	void InitMissleLaunch();
	void SpawnMissile();

	// ------------ ref missile blueprint class to fire -------- //
	UPROPERTY(EditDefaultsOnly, Category = "Reactor Projectiles")
		TSubclassOf<class AHomingMissile> MissileClass;

	// ------- you can add the static mesh and collision component here --------- //
};
