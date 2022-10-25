// Fill out your copyright notice in the Description page of Project Settings.


#include "ReactorBoss.h"
#include "HomingMissile.h"
#include "GameFramework/Actor.h"

// Sets default values
AReactorBoss::AReactorBoss(const FObjectInitializer& objInit)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ---------- construct collision component ------------ //

	// -------- construct mesh compoennt ------------- //

}

// Called when the game starts or when spawned
void AReactorBoss::BeginPlay()
{
	Super::BeginPlay();
	InitMissleLaunch();
}

// Called every frame
void AReactorBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AReactorBoss::InitMissleLaunch()
{
	GetWorldTimerManager().SetTimer(missleTimerHandle, this, &AReactorBoss::SpawnMissile, 3.0f, true);
}

void AReactorBoss::SpawnMissile()
{
	if (MissileClass != NULL)
	{
		UWorld* const world = GetWorld();

		if (world != NULL)
		{
			FVector currentPos = GetActorLocation();
			FRotator currentRot = FRotator(0.0f, 0.0f, 0.0f);

			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;
			spawnParams.Instigator = GetInstigator();

			AHomingMissile* FiredMissiles = world->SpawnActor<AHomingMissile>(MissileClass, currentPos, currentRot, spawnParams);

			if (FiredMissiles != nullptr)
			{
				// ------- setting the mesh rotation offset, depending on how the missle FBX was modeled ----------- //
				FRotator meshRot = FiredMissiles->MissileMesh->GetComponentRotation();
				meshRot.Roll = 0.0f;
				meshRot.Pitch = -90.0f;
				meshRot.Yaw = 0.0f;
				FiredMissiles->MissileMesh->SetRelativeRotation(meshRot);
			}
		}
	}
}


