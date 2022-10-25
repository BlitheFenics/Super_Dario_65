// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_2.0/BTTask_FindPatrolPathPoint.h"
#include "AI_2.0/Enemy_AIController.h"
#include "AI_2.0/Enemy_AI.h"
#include "AI_2.0/Blackboard_Keys.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindPatrolPathPoint::UBTTask_FindPatrolPathPoint(FObjectInitializer const& objInit)
{
    NodeName = TEXT("Find Patrol Waypoints");
}


EBTNodeResult::Type UBTTask_FindPatrolPathPoint::ExecuteTask(UBehaviorTreeComponent& ownerComponent, uint8* nodeMemory)
{
    // ------------ get AI controller for the patrolling enemy ------------//
    AEnemy_AIController* const controller = Cast<AEnemy_AIController>(ownerComponent.GetAIOwner());

    // ----------------- get the current patrol path index from the blackboard --------- //
    int const index = controller->get_blackboard()->GetValueAsInt(bb_keys::patrolPathIndex);

    // ------------- use the index to get the current patrol path from the enemy's reference to the patrol path ---------- //
    AEnemy_AI* const enemy = Cast<AEnemy_AI>(controller->GetPawn());
    FVector const point = enemy->GetPatrolPath()->GetPatrolPoint(index);

    // --------------- transform this point to a global position using its parent ----------- //
    FVector const globalPoint = enemy->GetPatrolPath()->GetActorTransform().TransformPosition(point);

    // -------- write the current global path point to the blackboard --------- //
    controller->get_blackboard()->SetValueAsVector(bb_keys::patrolPathVector, globalPoint);

    // -------------- finish with success ------------- //
    FinishLatentTask(ownerComponent, EBTNodeResult::Succeeded);

    return EBTNodeResult::Succeeded;
}
