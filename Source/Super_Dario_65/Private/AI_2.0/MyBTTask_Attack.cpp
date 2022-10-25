// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_2.0/MyBTTask_Attack.h"
#include "AI_2.0/AttackInterface.h"
#include "AI_2.0/Enemy_AIController.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Engine/LatentActionManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"

UMyBTTask_Attack::UMyBTTask_Attack(FObjectInitializer const& objInit)
{
    NodeName = TEXT("Enemy Attack");
}


EBTNodeResult::Type UMyBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
    // ---------- get the enemy -------------- //
    AAIController* const controller = ownerComp.GetAIOwner();
    AEnemy_AI* const enemy = Cast<AEnemy_AI>(controller->GetPawn());

    if (IAttackInterface* const iAttack = Cast<IAttackInterface>(enemy))
    {
        if (montageFinished(enemy))

        {
            iAttack->Execute_attack(enemy);
        } }

    FinishLatentTask(ownerComp, EBTNodeResult::Succeeded);
    return EBTNodeResult::Succeeded;
}

bool UMyBTTask_Attack::montageFinished(AEnemy_AI* const enemy)
{
    return enemy->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(enemy->GetMontage());
}
