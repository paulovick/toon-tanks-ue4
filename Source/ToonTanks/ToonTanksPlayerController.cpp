// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"

void AToonTanksPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
	if (bPlayerEnabled)
	{
		GetPawn()->EnableInput(this);
		CurrentMouseCursor = EMouseCursor::Crosshairs;
	}
	else
	{
		GetPawn()->DisableInput(this);
		CurrentMouseCursor = EMouseCursor::Default;
	}
}
