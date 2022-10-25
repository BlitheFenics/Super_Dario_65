// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "AI_2.0/Enemy_AI.h"
#include "BTTask_ChasePlayer.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SUPER_DARIO_65_API UBTTask_ChasePlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
		
public:
	UBTTask_ChasePlayer(FObjectInitializer const& objInit);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory) override;
	
};
