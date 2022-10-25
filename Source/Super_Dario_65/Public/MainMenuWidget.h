// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class SUPER_DARIO_65_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()


		UFUNCTION(BlueprintCallable, Category = "ButtonSelect")
		void Play(bool pressed);

	UFUNCTION(BlueprintCallable, Category = "ButtonSelect")
		void Controls(bool pressed);

	UFUNCTION(BlueprintCallable, Category = "ButtonSelect")
		void Credits(bool pressed);

	UFUNCTION(BlueprintCallable, Category = "ButtonSelect")
		void Options(bool pressed);

	UFUNCTION(BlueprintCallable, Category = "ButtonSelect")
		void Stats(bool pressed);
};
