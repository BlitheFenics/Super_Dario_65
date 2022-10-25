// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "GameFramework/Pawn.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "UObject/UObjectGlobals.h"

#include "BTTask_FindRandomLocation.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SUPER_DARIO_65_API UBTTask_FindRandomLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_FindRandomLocation(FObjectInitializer const& obj_init);
	// ---------- the execute function ------------ //
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& ownerComponent, uint8* nodeMemory) override;

private:
	// ------- the search radius ----------- //
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Search, meta = (AllowPrivateAccess = "true"))
	float searchRadius;
};
