// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

#include "HealthComponent.h"
#include "HealthWidget.h"
#include "Tank.h"
#include "TimerManager.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

ATower::ATower()
{
	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Health Widget"));
	HealthWidgetComponent->SetupAttachment(RootComponent);
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(
		FireRateTimerHandle,
		this,
		&ATower::CheckFireCondition,
		FireRate,
		true
	);

	HealthWidget = Cast<UHealthWidget>(HealthWidgetComponent->GetWidget());
	if (!HealthWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("Health widget not found for: %s"), *GetName());
	}
	
	if (HealthComponent)
	{
		HealthComponent->OnHealthUpdated.AddDynamic(this, &ATower::OnHealthUpdated);
		if (HealthWidget)
		{
			HealthWidget->UpdateHealth(HealthComponent->GetHealth(), HealthComponent->GetMaxHealth());
		}
	}
}

void ATower::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (InFireRange())
	{
		RotateTurret(Tank->GetActorLocation());
	}
}

int32 ATower::GetProvidedXP()
{
	return ProvidedXP;
}

void ATower::DisableFire()
{
	bFireEnabled = false;
}


float ATower::GetProjectileDamage()
{
	return ProjectileDamage;
}


void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::CheckFireCondition()
{
	if (!Tank) return;
	if (InFireRange() && Tank->bAlive && bFireEnabled)
	{
		Fire();
	}
}

bool ATower::InFireRange()
{
	if (Tank)
	{
		const float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

		return Distance <= FireRange;
	}

	return false;
}

void ATower::OnHealthUpdated(float Health, float MaxHealth)
{
	if (HealthWidget)
	{
		HealthWidget->UpdateHealth(Health, MaxHealth);
	}
}
