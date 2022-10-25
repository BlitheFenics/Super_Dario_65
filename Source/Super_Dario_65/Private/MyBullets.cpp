// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBullets.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AMyBullets::AMyBullets()
{
	// ------- making the empty bullet mesh for the class blueprint --------- //
	bulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	bulletMesh->SetupAttachment(RootComponent);
	
	// ------- making the collision box ---------- //
	bulletCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	bulletCollision->SetupAttachment(bulletMesh);

	// ------- sets up a notification for when this component hits something blocking ------- //
	bulletCollision->OnComponentBeginOverlap.AddDynamic(this, &AMyBullets::OnBoxComponentHit);

	bulletCollision->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.0f));
	bulletCollision->CanCharacterStepUpOn = ECB_No;

	// ------ using the built in projectile movement componet to make up how the bullet moves --------- //
	bulletMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BulletComponent"));
	bulletMovement->UpdatedComponent = bulletCollision; // this updates the movement based on what's happening with the collision.
	bulletMovement->InitialSpeed = 1000.0f;
	bulletMovement->MaxSpeed = 1000.0f;
	bulletMovement->bRotationFollowsVelocity = true;
	bulletMovement->ComputeVelocity(FVector(3000.0f, 1.0f, 1.0f), 1.0f);
	// ------ setting the total amount of time before bullet dies by default ------- //
	InitialLifeSpan = 1.0f;
}

void AMyBullets::OnBoxComponentHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// ----------- only add impulse and destroys the bullet if it hits anything with physics on ------- //
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		Destroy();
	}

}




