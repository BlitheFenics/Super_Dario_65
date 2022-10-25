// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BTTask_IncrementPathIndex.generated.h"

/**
 * 
 */
UCLASS()
class SUPER_DARIO_65_API UBTTask_IncrementPathIndex : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTTask_IncrementPathIndex(FObjectInitializer const& objInit);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& ownerComponent, uint8* nodeMemory) override;

private:
	enum class DirectionType
	{
		FORWARD,
		REVERSE
	};

	DirectionType direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Search, meta = (AllowPrivateAccess = "true"))
		bool biDirectional;

};
