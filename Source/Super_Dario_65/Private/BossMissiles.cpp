// Fill out your copyright notice in the Description page of Project Settings.


#include "BossMissiles.h"
#include "Characters/DarioBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "EngineUtils.h"

// Sets default values
ABossMissiles::ABossMissiles(const FObjectInitializer& ObjectInit) : Super(ObjectInit)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MissileMesh = ObjectInit.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Missile Mesh"));
	MissileMesh->SetupAttachment(RootComponent);

	// -------- setup for the collision component -------------- //
	CollisionBox = ObjectInit.CreateDefaultSubobject<UBoxComponent>(this, TEXT("Box Collider"));
	CollisionBox->SetupAttachment(MissileMesh);

	// ----------- set up the projectile movement component ------------ //
	ProjectileMovement = ObjectInit.CreateDefaultSubobject<UProjectileMovementComponent>(this, TEXT("Projectile Movement"));
	ProjectileMovement->UpdatedComponent = CollisionBox;
	ProjectileMovement->InitialSpeed = 2000.0f;
	ProjectileMovement->MaxSpeed = 3000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bInitialVelocityInLocalSpace = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->HomingAccelerationMagnitude = 1.0f;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	ProjectileMovement->Velocity - FVector(0.0f, 0.0f, 0.0f);

	// ------------ binding the overlap event ------------ //
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABossMissiles::OnOverlapBegin);

	// ------- default values for variables --------- //
	hasTargetPosition = false;
	hasNoTarget = false;
	target = NULL;
	delayTimer = 0.0f;
	hasFinishedDelay = false;
	lifetimeCountdown = 15.0f;
	canBeDestroyed = false;
	playerInWorld = NULL;

}


// Called when the game starts or when spawned
void ABossMissiles::BeginPlay()
{
	Super::BeginPlay();
	FindDario();

	// ------- before finding the target, launch missle upwards --------- //
	if (!hasTargetPosition)
	{
		ProjectileMovement->Velocity = GetActorUpVector() * 300.0f;

		// --------- beginplay with collision disables so missile does not interact with other actors ------------- //
		this->SetActorEnableCollision(false);
	}
	
}

// ------- this with find the missiles target ---------- //
void ABossMissiles::FindDario()
{
	class UWorld* const world = GetWorld();
	
	if (world)
	{
		for (TActorIterator<ADarioBase> ObstacleItr(world); ObstacleItr; ++ObstacleItr)
		{
			FName PlayerTagName = FName(TEXT("Player"));
			class ADarioBase* foundPlayer = *ObstacleItr;

			if (foundPlayer != nullptr)
			{
				if (foundPlayer->ActorHasTag(PlayerTagName))
				{
					if (playerInWorld != foundPlayer)
					{
						playerInWorld = foundPlayer;
					}
				}
			}
		}
	}

	playerInWorld = (ADarioBase*)world->GetFirstPlayerController()->GetPawn();


}

// Called every frame
void ABossMissiles::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!hasFinishedDelay)
	{
		Delay(DeltaTime);
	}
	else
	{
		// ------------ if a target is found, move the missile actor toward target ---------- //
		if (hasTargetPosition)
		{
			if (target != NULL)
			{
				if (target->IsValidLowLevel())
				{
					FVector dir = (target->GetActorLocation() - GetActorLocation()).GetSafeNormal();
					dir += target->GetVelocity() * dir.Size() / 200.0f;
					ProjectileMovement->Velocity += dir * 200.0f * DeltaTime;
					ProjectileMovement->Velocity = ProjectileMovement->Velocity.GetSafeNormal() * 200.0f;

					//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("velocity: %v"), ProjectileMovement->Velocity);

					//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("velocity %f, %f, %f"), ProjectileMovement->Velocity.X, ProjectileMovement->Velocity.Y, ProjectileMovement->Velocity.Z));
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("speed %f"), GetActorLocation().X));
				}
				else
				{
					if (!this->IsPendingKill())
					{
						if (this->IsValidLowLevel())
						{
							K2_DestroyActor();
						}
					}
				}
			}
			else
			{
				// --------- if a target hasn't been found, move missile upwards -------- //
				if (hasNoTarget)
				{
					ProjectileMovement->Velocity = GetActorUpVector() * 200.0f;
					hasNoTarget = false;
				}
			}
		}

		// ------------- destroy the missile after 15 second countdown -------------- //
		lifetimeCountdown -= 1 * DeltaTime;
		if (lifetimeCountdown <= 0.0f)
		{
			if (!canBeDestroyed)
			{
				canBeDestroyed = true;
				target = nullptr;
				Explode();
			}
		}
	}
}

void ABossMissiles::Explode()
{
	// ----- play explosion ------ //

	// ---- play explosion sound ------ //
	
	if (this->IsValidLowLevel())
	{
		Destroy();
	}
}

// --------- waits one second before finding the target ------------ //
void ABossMissiles::Delay(float deltaTime)
{
	if (!hasFinishedDelay)
	{
		delayTimer += 1.0f * deltaTime;

		if (delayTimer > 1.0f)
		{
			UpdateTarget();
			this->SetActorEnableCollision(true);
			hasFinishedDelay = true;
		}
	}
}



void ABossMissiles::UpdateTarget()
{
	if (!hasTargetPosition)
	{
		if (playerInWorld != NULL)
		{
			if (playerInWorld->IsValidLowLevel())
			{
				target = playerInWorld;
				hasTargetPosition = true;
				hasNoTarget = false;

				// -------- keep the mesh rotation offset --------- //
				FRotator rotVal = MissileMesh->GetComponentRotation();
				rotVal.Roll = 0.0f;
				rotVal.Pitch = -90.0f;
				rotVal.Yaw = 0.0f;
				MissileMesh->SetRelativeRotation(rotVal);
			}
			else
			{
				target = nullptr;
				hasTargetPosition = true;
				hasNoTarget = true;
			}
		}
		else
		{
			target = nullptr;
			hasTargetPosition = true;
			hasNoTarget = true;
		}
	}
	
}



void ABossMissiles::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADarioBase* darioPlayer = Cast<ADarioBase>(OtherActor);
	// --------- need the ground to be dected here -------- //

	if (darioPlayer)
	{
		// ---- play the particle system here ---- //
		
		// ---- play the sound effect here ------ //


		if (this->IsValidLowLevel())
		{
			Destroy();
		}
	}

	// ------ for the ground check ---------
	// if(ground)
	// {
	//		play particle
	//		play the sound
	//		 if(this->IsValidLowLevel())
	//		destroy();
	// }
}


