// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthUpdatedDelegate, float, Health);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UHealthComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	float GetHealth() const;

	UFUNCTION(BlueprintCallable)
	float GetMaxHealth() const;

	UPROPERTY()
	FOnHealthUpdatedDelegate OnHealthUpdated;

	void UpgradeMaxHealth();

protected:

	virtual void BeginPlay() override;

private:
	
	UPROPERTY()
	class AToonTanksGameMode* ToonTanksGameMode;

	UPROPERTY(EditAnywhere)
	float InitialMaxHealth = 100.f;
	float MaxHealth = 0.f;
	float Health = 0.f;

	UPROPERTY(EditAnywhere)
	float HealthIncrementPerLevel = 40.f;

	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser);
};
