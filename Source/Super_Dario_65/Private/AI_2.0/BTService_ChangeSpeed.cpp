// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_2.0/BTService_ChangeSpeed.h"
#include "AI_2.0/Enemy_AI.h"
#include "AI_2.0/Enemy_AIController.h"
#include "GameFramework/CharacterMovementComponent.h"



UBTService_ChangeSpeed::UBTService_ChangeSpeed()
{
	NodeName = TEXT("Change Speed");
	
	speed = 600.0f;
	bNotifyBecomeRelevant = true;

}

void UBTService_ChangeSpeed::OnBecomeRelevant(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	Super::OnBecomeRelevant(ownerComp, nodeMemory);

	auto const controller = ownerComp.GetAIOwner();
	AEnemy_AI* const enemy = Cast<AEnemy_AI>(controller->GetPawn());
	enemy->GetCharacterMovement()->MaxWalkSpeed = speed;

}

FString UBTService_ChangeSpeed::GetStaticServiceDescription() const
{
	return FString("Change the enemy speed.");
}
