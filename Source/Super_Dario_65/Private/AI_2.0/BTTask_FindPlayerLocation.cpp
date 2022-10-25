// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_2.0/BTTask_FindPlayerLocation.h"
#include "AI_2.0/Enemy_AIController.h"
#include "AI_2.0/Blackboard_Keys.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"


UBTTask_FindPlayerLocation::UBTTask_FindPlayerLocation(FObjectInitializer const& obj_init)
{
    NodeName = TEXT("Find Player Location");

    searchRandom = false;
    searchRadius = 150.0f;
}


EBTNodeResult::Type UBTTask_FindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
    // ----------- get player character and the enemy controller ----------- //
    ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    auto const controller = Cast<AEnemy_AIController>(ownerComp.GetAIOwner());

    // ------------ get player location to use as an origin --------------- //
    FVector const playerLocation = player->GetActorLocation();

    if (searchRandom)
    {
        FNavLocation location;

        // ----------- get the navigation system and generate a random location near the player ------------ //
        UNavigationSystemV1* const navSys = UNavigationSystemV1::GetCurrent(GetWorld());

        if (navSys->GetRandomPointInNavigableRadius(playerLocation, searchRadius, location, /*navSys->GetDefaultNavDataInstance(),*/ nullptr))
        {
            controller->get_blackboard()->SetValueAsVector(bb_keys::targetLocation, location.Location);
        }
        else
        {
            controller->get_blackboard()->SetValueAsVector(bb_keys::targetLocation, playerLocation);
        }

        // -------------- finish with a success ---------- //
        FinishLatentTask(ownerComp, EBTNodeResult::Succeeded);

    }

    return EBTNodeResult::Succeeded;
}
