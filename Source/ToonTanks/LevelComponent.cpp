// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelComponent.h"

ULevelComponent::ULevelComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	XP = GetRequiredXPForLevel(Level);
}

void ULevelComponent::BeginPlay()
{
	Super::BeginPlay();
}

float ULevelComponent::GetProjectileDamage()
{
	return BaseProjectileDamage + Level * ProjectileDamageGainPerLevel;
}

void ULevelComponent::AddXP(int32 NewXP)
{
	XP += NewXP;
	UE_LOG(LogTemp, Warning, TEXT("New XP: %d"), XP);

	if (GetRequiredXPForLevel(Level + 1) <= XP)
	{
		UpgradeLevel(Level + 1);
	}
}

void ULevelComponent::UpgradeLevel(int32 NewLevel)
{
	Level = NewLevel;
	UE_LOG(LogTemp, Warning, TEXT("New Level: %d"), Level);
	OnLevelUp.Broadcast(Level);
}


int32 ULevelComponent::GetRequiredXPForLevel(int32 Level)
{
	return FMath::Pow(2, Level) * 10;
}


