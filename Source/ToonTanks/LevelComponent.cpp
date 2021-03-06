// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelComponent.h"

#include "HealthComponent.h"
#include "LevelUpWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

ULevelComponent::ULevelComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	XP = GetRequiredXPForLevel(Level);
}

void ULevelComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!LevelUpWidgetTemplate)
	{
		UE_LOG(LogTemp, Error, TEXT("Level Up Widget not found in %s!"), *GetOwner()->GetName());
	}

	HealthComponent = Cast<UHealthComponent>(GetOwner()->GetComponentByClass(UHealthComponent::StaticClass()));
	if (!HealthComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Health Component not found in %s!"), *GetOwner()->GetName());
	}

	OnXPUpdated.Broadcast(XP, Level);
	OnLevelUp.Broadcast(Level);
}

float ULevelComponent::GetProjectileDamage()
{
	return BaseProjectileDamage + Level * ProjectileDamageGainPerLevel;
}

int32 ULevelComponent::GetXP() const
{
	return XP;
}

int32 ULevelComponent::GetLevel() const
{
	return Level;
}

void ULevelComponent::AddXP(int32 NewXP)
{
	XP += NewXP;

	if (GetRequiredXPForLevel(Level + 1) <= XP)
	{
		UpgradeLevel(Level + 1);
	}

	OnXPUpdated.Broadcast(XP, Level);
}

void ULevelComponent::UpgradeLevel(int32 NewLevel)
{
	Level = NewLevel;

	OnLevelUp.Broadcast(Level);

	if (LevelUpWidgetTemplate && HealthComponent)
	{
		ULevelUpWidget* LevelUpWidget = Cast<ULevelUpWidget>(CreateWidget(GetOwner()->GetWorld(), LevelUpWidgetTemplate, FName("Level Up Widget")));
		LevelUpWidget->DisplayLevelUp(
			GetProjectileDamage(),
			ProjectileDamageGainPerLevel,
			HealthComponent->GetMaxHealth(),
			HealthComponent->GetHealthIncrementPerLevel()
		);
		LevelUpWidget->AddToViewport(0);
	}
}


int32 ULevelComponent::GetRequiredXPForLevel(int32 Level)
{
	return FMath::Pow(2, Level) * 10;
}


