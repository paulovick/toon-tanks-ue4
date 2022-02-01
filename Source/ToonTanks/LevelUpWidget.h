// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelUpWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ULevelUpWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent)
	void DisplayLevelUp(float NewDamage, float DamageIncrease, float NewMaxHealth, float HealthIncrease);
};
