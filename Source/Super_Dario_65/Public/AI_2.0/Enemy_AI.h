// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AI_2.0/EnemyAI_Waypoints.h"
#include "AI_2.0/AttackInterface.h"
#include "Animation/AnimMontage.h"
#include "Enemy_AI.generated.h"

UCLASS()
class SUPER_DARIO_65_API AEnemy_AI : public ACharacter, public IAttackInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy_AI();

	AEnemyAI_Waypoints* GetPatrolPath();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
		UAnimMontage* SpinAttack;

	// To play attack animation:
	// PlayAnimMontage(Melee);

	int melee_attack_Implementaion();

	UAnimMontage* GetMontage() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess = "true"))
	AEnemyAI_Waypoints* patrolPath;
	


};
