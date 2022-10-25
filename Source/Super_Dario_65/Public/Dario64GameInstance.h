// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Dario64GameInstance.generated.h"


USTRUCT(Blueprintable)
struct FULevelStats
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(BlueprintReadWrite)
		int RodsCollected;

	UPROPERTY(BlueprintReadWrite)
		int BeerCollected;

	UPROPERTY(BlueprintReadWrite)
		int BulletsFired;

	UPROPERTY(BlueprintReadWrite)
		int MugsCollected;

	UPROPERTY(BlueprintReadWrite)
		float TimeCompleted;
};
/**
 * 
 */
UCLASS()
class SUPER_DARIO_65_API UDario64GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
		int totalRodsCollected;

	UPROPERTY(BlueprintReadWrite)
		int totalBeerCollected;

	UPROPERTY(BlueprintReadWrite)
		int totalBulletsFired;

	UPROPERTY(BlueprintReadWrite)
		int totalMugsCollected;

	UPROPERTY(BlueprintReadWrite)
		int currentLevel;

	UPROPERTY(BlueprintReadWrite)
		int MAX_CONTROLLERS;

	UPROPERTY(BlueprintReadWrite)
		int ActiveControllerID;

	UPROPERTY(BlueprintReadWrite)
		float VolumeMusic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FULevelStats levelOne;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FULevelStats levelTwo;

};
	
