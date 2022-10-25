// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "Enemy_AIController.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;
class UBehaviorTree;
class UAISenseConfig_Sight;
class UAIPerceptionComponent;

UCLASS()
class SUPER_DARIO_65_API AEnemy_AIController : public AAIController
{
	GENERATED_BODY()

public:
		AEnemy_AIController(FObjectInitializer const& obj_init = FObjectInitializer::Get());

		void BeginPlay() override;
		void OnPossess(APawn* const pawn) override;

		UBlackboardComponent* get_blackboard() const;

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess = "true"))
		UBehaviorTreeComponent* behaviorTreeComponent;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess = "true"))
		UBehaviorTree* behaviorTree;

	UFUNCTION()
		void OnTargetDetected(AActor* actor, FAIStimulus const stimulus);

	void SetupPerceptionSystem();

	UBlackboardComponent* blackboard;

	UAISenseConfig_Sight* sightConfig;



};
