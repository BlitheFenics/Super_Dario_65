// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_2.0/BTTask_IncrementPathIndex.h"
#include "AI_2.0/Enemy_AI.h"
#include "AI_2.0/Enemy_AIController.h"
#include "AI_2.0/Blackboard_Keys.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <cmath>

UBTTask_IncrementPathIndex::UBTTask_IncrementPathIndex(FObjectInitializer const& objInit)
{
	NodeName = TEXT("Increment Path Index");

	direction = DirectionType::FORWARD;
	biDirectional = true; // if you tick this off, the AI will move in the same direction, a full loop. 
						 // if true, then the AI will go from points in a half loop.
}


EBTNodeResult::Type UBTTask_IncrementPathIndex::ExecuteTask(UBehaviorTreeComponent& ownerComponent, uint8* nodeMemory)
{
	// ------ get the AI controller ---------- //

	AEnemy_AIController* const controller = Cast<AEnemy_AIController>(ownerComponent.GetAIOwner());
	AEnemy_AI* const enemy = Cast<AEnemy_AI>(controller->GetPawn());
	int const numOfPoints = enemy->GetPatrolPath()->num();
	int const minIndex = 0;
	int const maxIndex = numOfPoints - 1;

	// --------- get and set the blackboard index key ------------- //

	int index = controller->get_blackboard()->GetValueAsInt(bb_keys::patrolPathIndex);
	if (biDirectional)
	{
		if (index >= maxIndex && direction == DirectionType::FORWARD)
		{
			direction = DirectionType::REVERSE;
		}
		else if (index == minIndex && direction == DirectionType::REVERSE)
		{
			direction = DirectionType::FORWARD;
		}
	}

	// ------- if enemy is going forwards, increment it otherwise decrement it, dividing the number of points -------- //
	controller->get_blackboard()->SetValueAsInt(bb_keys::patrolPathIndex, (direction == DirectionType::FORWARD ? std::abs(++index) : std::abs(--index)) % numOfPoints);

	// ------ success as always finishes this! --------- //
	FinishLatentTask(ownerComponent, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}
