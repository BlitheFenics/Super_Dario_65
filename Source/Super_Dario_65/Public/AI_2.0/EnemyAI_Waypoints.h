// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyAI_Waypoints.generated.h"

UCLASS()
class SUPER_DARIO_65_API AEnemyAI_Waypoints : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyAI_Waypoints();

	FVector GetPatrolPoint(int const index) const;
	int num() const;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI, meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
		TArray<FVector> patrolPoints;
};
