// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
//#include "NiagaraComponent.h"
#include "PortalComputer.generated.h"

class ADarioBase;


UCLASS()
class SUPER_DARIO_65_API APortalComputer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortalComputer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		class UStaticMeshComponent* mesh;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int DestinationLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector DarioPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterial* dissolveMat;
	UPROPERTY()
		UMaterialInstanceDynamic* disMat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SplineInfo)
		class UCurveFloat* CurveFloat;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SplineInfo)
		class UCurveFloat* FadeFloat;


	UFUNCTION()
		void OnTimelineProgress(float value);
	UFUNCTION()
		void OnFadeTimelineProgress(float value);

	UFUNCTION()
		void OnTimelineComplete(float value);
	UFUNCTION()
		void OnFadeTimelineComplete(float value);


	UFUNCTION()
		void Transition(ADarioBase* dar);

	UFUNCTION(BlueprintNativeEvent)
		void TheParticleEvent();

	UFUNCTION()
		void FadeDario();

	FTimeline Timeline;
	FTimeline FadeTimeline;

	UPROPERTY()
		FVector StartLoc;
	UPROPERTY()
		FVector EndLoc;

	UPROPERTY()
		ADarioBase* dario;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//UFUNCTION(BlueprintCallable)
	//	void 

};
