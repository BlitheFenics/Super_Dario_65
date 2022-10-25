// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "AI_2.0/Enemy_AI.h"
#include "MyBTTask_Attack.generated.h"

/**
 * 
 */
UCLASS()
class SUPER_DARIO_65_API UMyBTTask_Attack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UMyBTTask_Attack(FObjectInitializer const& objInit);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory) override;

private:
	bool montageFinished(AEnemy_AI* const enemy);
};
