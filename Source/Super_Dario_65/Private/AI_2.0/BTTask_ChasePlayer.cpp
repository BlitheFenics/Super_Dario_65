// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_2.0/BTTask_ChasePlayer.h"
#include "AI_2.0/Enemy_AIController.h"
#include "AI_2.0/Blackboard_Keys.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"


UBTTask_ChasePlayer::UBTTask_ChasePlayer(FObjectInitializer const& objInit)
{
	NodeName = TEXT("Chase Player");
}


EBTNodeResult::Type UBTTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	// ------ get target location from blackboard with ai controller --------- //
	AEnemy_AIController* const controller = Cast<AEnemy_AIController>(ownerComp.GetAIOwner());
	FVector const playerLocation = controller->get_blackboard()->GetValueAsVector(bb_keys::targetLocation);

	// ----------- move to player location --------- //
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(controller, playerLocation);

	// --------------- finish with the usual success ------------ //
	FinishLatentTask(ownerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
