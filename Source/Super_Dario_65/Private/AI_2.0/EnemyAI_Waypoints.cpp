// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_2.0/EnemyAI_Waypoints.h"

// Sets default values
AEnemyAI_Waypoints::AEnemyAI_Waypoints()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

FVector AEnemyAI_Waypoints::GetPatrolPoint(int const index) const
{
	return patrolPoints[index];
}

int AEnemyAI_Waypoints::num() const
{
	return patrolPoints.Num();
}
