// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_2.0/BTTask_FindRandomLocation.h"
#include "AI_2.0/Enemy_AIController.h"
#include "AI_2.0/Blackboard_Keys.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

// ------ using the contructor to add a name to the node --------- //
UBTTask_FindRandomLocation::UBTTask_FindRandomLocation(FObjectInitializer const& obj_init)
{
	NodeName = TEXT("Find Random Location");
	searchRadius = 1500.0f;
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& ownerComponent, uint8* nodeMemory)
{
	/// ----- get AI controller and the enemy -------- //
	auto const controller = Cast<AEnemy_AIController>(ownerComponent.GetAIOwner());
	auto const enemy = controller->GetPawn();

	// --------- get the enemy location to use as an origin location ------ //
	FVector const origin = enemy->GetActorLocation();
	FNavLocation location;
	
	// ---------------- get the navigation system and generate a random location on the Navmesh --------- //
	UNavigationSystemV1* const navSystem = UNavigationSystemV1::GetCurrent(GetWorld());

	if (navSystem->GetRandomPointInNavigableRadius(origin, searchRadius, location, /*navSystem->GetDefaultNavDataInstance(),*/ nullptr))
	{
		controller->get_blackboard()->SetValueAsVector(bb_keys::targetLocation, location.Location);
	}

	UE_LOG(LogTemp, Warning, TEXT("Location: %f"), bb_keys::targetLocation);

	// ----- finish with sUCCESS ------ //
	FinishLatentTask(ownerComponent, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}
