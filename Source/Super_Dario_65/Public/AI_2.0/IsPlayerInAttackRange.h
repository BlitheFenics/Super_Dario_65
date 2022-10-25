// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "IsPlayerInAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class SUPER_DARIO_65_API UIsPlayerInAttackRange : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UIsPlayerInAttackRange();
	void OnBecomeRelevant(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory) override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess = "true"))
	float attackRange;
};
