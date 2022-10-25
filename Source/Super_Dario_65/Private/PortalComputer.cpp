// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalComputer.h"
#include "Characters/DarioBase.h"
//#include "D:/EpicLibrary/UE_4.26/Engine/Plugins/FX/Niagara/Source/Niagara/Private/NiagaraComponent.cpp"


// Sets default values
APortalComputer::APortalComputer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("BigComputer"));
	mesh->SetupAttachment(RootComponent);

	
}

void APortalComputer::OnTimelineProgress(float value)
{
	FVector newLoc = FMath::Lerp(StartLoc, EndLoc, value);
	dario->SetActorLocation(newLoc);

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("STILL GOING"));
}

void APortalComputer::OnFadeTimelineProgress(float value)
{
	disMat->SetScalarParameterValue("Dissolve", value);
	//rio->GetMesh()->GetMaterial(0)->inst//
}

void APortalComputer::OnTimelineComplete(float value)
{
	FadeDario();
}

void APortalComputer::OnFadeTimelineComplete(float value)
{
}


void APortalComputer::Transition(ADarioBase* dar)
{

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("COMMENCE TRANSITION"));
	dario = dar;

	StartLoc = dario->GetActorLocation();
	EndLoc = DarioPosition;
	EndLoc.Z = StartLoc.Z;

	dario->DisableGun();

	Timeline.PlayFromStart();
}

void APortalComputer::TheParticleEvent_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("ACTIVATING PARTICLES"));

}

void APortalComputer::FadeDario()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("FADE DARIO"));

	//disMat = dario->GetMesh()->CreateDynamicMaterialInstance(0, dissolveMat);
	disMat = UMaterialInstanceDynamic::Create(dissolveMat, this);
	dario->GetMesh()->SetMaterial(0, disMat);
	disMat->SetScalarParameterValue("Dissolve", 0.7);
	dario->GetMesh()->SetMaterial(0, disMat);
	
	TheParticleEvent();

	FadeTimeline.PlayFromStart();


}

// Called when the game starts or when spawned
void APortalComputer::BeginPlay()
{
	Super::BeginPlay();

	if (CurveFloat)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("OnTimelineProgress"));

		FOnTimelineEventStatic TimelineComplete;
		TimelineComplete.BindUFunction(this, FName("OnTimelineComplete"));

		Timeline.AddInterpFloat(CurveFloat, TimelineProgress);
		Timeline.SetLooping(false);

		Timeline.SetTimelineFinishedFunc(TimelineComplete);
	}

	if (FadeFloat)
	{
		FOnTimelineFloat FadeProgress;
		FadeProgress.BindUFunction(this, FName("OnFadeTimelineProgress"));

		FOnTimelineEventStatic FadeComplete;
		FadeComplete.BindUFunction(this, FName("OnFadeTimelineComplete"));

		FadeTimeline.AddInterpFloat(FadeFloat, FadeProgress);
		FadeTimeline.SetLooping(false);

		FadeTimeline.SetTimelineFinishedFunc(FadeComplete);
	}
	
}

// Called every frame
void APortalComputer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Timeline.TickTimeline(DeltaTime);
	FadeTimeline.TickTimeline(DeltaTime);

}

