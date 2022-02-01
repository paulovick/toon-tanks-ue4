// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:

	ATower();

	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();
	int32 GetProvidedXP();

protected:

	virtual void BeginPlay() override;
	virtual float GetProjectileDamage() override;

private:
	
	class ATank* Tank;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float FireRange = 500.f;

	FTimerHandle FireRateTimerHandle;
	float FireRate = 2.f;
	void CheckFireCondition();
	
	bool InFireRange();
	
	class UHealthWidget* HealthWidget;

	UPROPERTY(VisibleAnywhere, Category = "Widgets")
	class UWidgetComponent* HealthWidgetComponent;

	UFUNCTION()
	void OnHealthUpdated(float Health, float MaxHealth);

	UPROPERTY(EditDefaultsOnly, Category = "XP")
	int32 ProvidedXP = 10;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float ProjectileDamage = 40.f;
};
