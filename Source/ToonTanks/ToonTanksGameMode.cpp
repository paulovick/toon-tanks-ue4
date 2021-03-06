// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"

#include "Tank.h"
#include "ToonTanksPlayerController.h"
#include "Tower.h"
#include "Engine/TriggerVolume.h"
#include "Kismet/GameplayStatics.h"

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if (ToonTanksPlayerController)
	{
		ToonTanksPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimeHandle;
		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
			ToonTanksPlayerController,
			&AToonTanksPlayerController::SetPlayerEnabledState,
			true
		);

		GetWorldTimerManager().SetTimer(
			PlayerEnableTimeHandle,
			PlayerEnableTimerDelegate,
			StartDelay,
			false
		);

		TArray<AActor*> TriggerVolumes;
		UGameplayStatics::GetAllActorsOfClass(this, ATriggerVolume::StaticClass(), TriggerVolumes);
		if (TriggerVolumes.Num() > 0)
		{
			EndTriggerVolume = Cast<ATriggerVolume>(TriggerVolumes[0]);
			if (EndTriggerVolume)
			{
				EndTriggerVolume->OnActorBeginOverlap.AddDynamic(this, &AToonTanksGameMode::ActorEnteredEndZone);
			}
		}
	}
}

void AToonTanksGameMode::HandleGameOver(bool bWon)
{
	GameOver(bWon);

	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);

	for (AActor* Actor : Towers)
	{
		ATower* Tower = Cast<ATower>(Actor);
		if (Tower)
		{
			Tower->DisableFire();
		}
	}
}


void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		if (ToonTanksPlayerController)
		{
			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}
		HandleGameOver(false);
	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		if (Tank)
		{
			Tank->HandleDestroyedEnemy(DestroyedTower->GetProvidedXP());
		}
		DestroyedTower->HandleDestruction();
	}
}

void AToonTanksGameMode::ActorEnteredEndZone(AActor* OverlappedActor, AActor* OtherActor)
{
	if (ToonTanksPlayerController)
	{
		ToonTanksPlayerController->SetPlayerEnabledState(false);
	}
	HandleGameOver(true);
}
