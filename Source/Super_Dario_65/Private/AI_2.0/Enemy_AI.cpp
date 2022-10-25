// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_2.0/Enemy_AI.h"

#include "Runtime/Engine/Classes/Engine/World.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/PlayerController.h"

#include "Components/WidgetComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AEnemy_AI::AEnemy_AI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = true;
	bUseControllerRotationYaw = true;
}


int AEnemy_AI::melee_attack_Implementaion()
{
	if (SpinAttack)
	{
		PlayAnimMontage(SpinAttack);
	}
	return 0;
}

UAnimMontage* AEnemy_AI::GetMontage() const
{
	return SpinAttack;
}



// Called when the game starts or when spawned
void AEnemy_AI::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called to bind functionality to input
void AEnemy_AI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}




AEnemyAI_Waypoints* AEnemy_AI::GetPatrolPath()
{
	return patrolPath;
}

