// Fill out your copyright notice in the Description page of Project Settings.


#include "DarioAnimInstance.h"

#include "Characters/DarioBase.h"

UDarioAnimInstance::UDarioAnimInstance()
{
	Speed = 0.0f;
	AnimState = 0;
}

void UDarioAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AActor* Owner = GetOwningActor();
	ADarioBase* Dario = (ADarioBase*)GetOwningActor();

	
	
	if (Dario != nullptr)
	{
		Speed = Dario->GetVelocity().Size();
	}
}
