// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_2.0/IsPlayerInAttackRange.h"
#include "AI_2.0/Enemy_AIController.h"
#include "AI_2.0/Enemy_AI.h"
#include "AI_2.0/Blackboard_Keys.h"

#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"

UIsPlayerInAttackRange::UIsPlayerInAttackRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Is Player In Attack Range");
	attackRange = 25.0f;
}

void UIsPlayerInAttackRange::OnBecomeRelevant(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	Super::OnBecomeRelevant(ownerComp, nodeMemory);

	// --------- get the enemy! ------------- //
	AEnemy_AIController* const controller = Cast<AEnemy_AIController>(ownerComp.GetAIOwner());
	AEnemy_AI* const enemy = Cast<AEnemy_AI>(controller->GetPawn());

	// ---------- get player character -------- //
	ACharacter* const dario = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	// ------------ true or false depending on whether the player is within range ------------- //
	controller->get_blackboard()->SetValueAsBool(bb_keys::darioInAttackRange, enemy->GetDistanceTo(dario) <= attackRange);
}
