// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "HealthWidgetComponent.h"
#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

float UHealthComponent::GetHealth() const
{
	return Health;
}

float UHealthComponent::GetMaxHealth() const
{
	return MaxHealth;
}

float UHealthComponent::GetHealthIncrementPerLevel() const
{
	return HealthIncrementPerLevel;
}

void UHealthComponent::UpgradeMaxHealth()
{
	MaxHealth += HealthIncrementPerLevel;
	Health += HealthIncrementPerLevel;

	OnHealthUpdated.Broadcast(Health, MaxHealth);
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	MaxHealth = InitialMaxHealth;
	Health = MaxHealth;

	OnHealthUpdated.Broadcast(Health, MaxHealth);

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);

	ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser)
{
	if (Damage <= 0.f) return;

	Health -= Damage;

	OnHealthUpdated.Broadcast(Health, MaxHealth);

	if (Health <= 0.f)
	{
		ToonTanksGameMode->ActorDied(DamagedActor);
	}
}
