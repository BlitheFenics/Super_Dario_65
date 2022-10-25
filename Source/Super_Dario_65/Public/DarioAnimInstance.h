// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Animation/AnimInstance.h"
#include "DarioAnimInstance.generated.h"
/**
 * 
 */
UCLASS(transient, Blueprintable, hideCategories = AnimInstance, BlueprintType)
class UDarioAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UDarioAnimInstance();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		int AnimState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		float Speed;

	virtual void NativeUpdateAnimation(float DeltaTime) override;
};