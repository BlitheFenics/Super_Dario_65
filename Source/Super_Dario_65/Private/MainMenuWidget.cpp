// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"

void UMainMenuWidget::Play(bool pressed)
{
	if (pressed)
	{
		UGameplayStatics::OpenLevel(this, "LoadingLevel", true);
	}
}

void UMainMenuWidget::Controls(bool pressed)
{
	if (pressed)
	{
		UGameplayStatics::OpenLevel(this, "ControlsLevel", true);
	}
}

void UMainMenuWidget::Credits(bool pressed)
{
	if (pressed)
	{
		UGameplayStatics::OpenLevel(this, "CreditsLevel", true);
	}
}

void UMainMenuWidget::Options(bool pressed)
{
	if (pressed)
	{
		UGameplayStatics::OpenLevel(this, "OptionsLevel", true);
	}
}

void UMainMenuWidget::Stats(bool pressed)
{
	if (pressed)
	{
		UGameplayStatics::OpenLevel(this, "StatsLevel", true);
	}
}
