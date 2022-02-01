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

	class UHealthComponent* HealthComponent;

	UFUNCTION()
	void OnHealthUpdated(float Health);

	UPROPERTY(EditDefaultsOnly, Category = "XP")
	int32 ProvidedXP = 10;
};
