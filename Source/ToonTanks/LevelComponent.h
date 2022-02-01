// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LevelComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API ULevelComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	ULevelComponent();

	void AddXP(int32 NewXP);

protected:

	virtual void BeginPlay() override;

private:

	int32 XP = 0;
	UPROPERTY(EditAnywhere)
	int32 Level = 1;

	void UpgradeLevel(int32 NewLevel);
	static int32 GetRequiredXPForLevel(int32 Level);
};
