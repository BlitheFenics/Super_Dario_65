// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_2.0/Enemy_AIController.h"
#include "Characters/DarioBase.h"
#include "AI_2.0/Blackboard_Keys.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "UObject/ConstructorHelpers.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework/Character.h"

AEnemy_AIController::AEnemy_AIController(FObjectInitializer const& obj_init)
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> obj(TEXT("BehaviorTree'/Game/Blueprints/AI_2_0-BPS/EnemyAI_BT.EnemyAI_BT'"));

	if (obj.Succeeded())
	{
		behaviorTree = obj.Object;
	}
	behaviorTreeComponent = obj_init.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BTComponent"));
	blackboard = obj_init.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BBComponent"));

	// ----------- setting up perception below ----------- //
	SetupPerceptionSystem();
}

void AEnemy_AIController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(behaviorTree);
	behaviorTreeComponent->StartTree(*behaviorTree);
}

void AEnemy_AIController::OnPossess(APawn* const pawn)
{
	Super::OnPossess(pawn);

	if (blackboard)
	{
		blackboard->InitializeBlackboard(*behaviorTree->BlackboardAsset);
	}
}

UBlackboardComponent* AEnemy_AIController::get_blackboard() const
{
	return blackboard;
}

void AEnemy_AIController::SetupPerceptionSystem()
{
	// ------------- create and initialise sight config objects --------- //
	sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

	sightConfig->SightRadius = 500.f;
	sightConfig->LoseSightRadius = sightConfig->SightRadius + 20.0f;
	sightConfig->PeripheralVisionAngleDegrees = 90.0f;
	sightConfig->SetMaxAge(3.0f);
	sightConfig->AutoSuccessRangeFromLastSeenLocation = 500.0f;
	
	sightConfig->DetectionByAffiliation.bDetectEnemies = true;
	sightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	sightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	// ------------ adding sight configuration component to perception component ---------- //
	GetPerceptionComponent()->SetDominantSense(*sightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemy_AIController::OnTargetDetected);
	GetPerceptionComponent()->ConfigureSense(*sightConfig);
}

void AEnemy_AIController::OnTargetDetected(AActor* actor, FAIStimulus const stimulus)
{
	if (auto const ch = Cast<ADarioBase>(actor))
	{
		get_blackboard()->SetValueAsBool(bb_keys::canSeePlayer, stimulus.WasSuccessfullySensed());
	}
}
