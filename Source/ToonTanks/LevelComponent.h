// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LevelComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUpDelegate, int32, NewLevel);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API ULevelComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	ULevelComponent();

	void AddXP(int32 NewXP);
	float GetProjectileDamage();

	UFUNCTION(BlueprintCallable)
	int32 GetXP() const;
	UFUNCTION(BlueprintCallable)
	int32 GetLevel() const;
	UFUNCTION(BlueprintCallable)
	static int32 GetRequiredXPForLevel(int32 Level);

	UPROPERTY()
	FOnLevelUpDelegate OnLevelUp;

protected:

	virtual void BeginPlay() override;

private:

	int32 XP = 0;
	UPROPERTY(EditAnywhere)
	int32 Level = 1;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float BaseProjectileDamage = 40.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float ProjectileDamageGainPerLevel = 5.f;

	void UpgradeLevel(int32 NewLevel);
};
