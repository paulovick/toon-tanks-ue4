// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "HealthComponent.h"
#include "LevelComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

APlayerController* ATank::GetTankPlayerController() const
{
	return TankPlayerController;
}


void ATank::BeginPlay()
{
	Super::BeginPlay();

	TankPlayerController = Cast<APlayerController>(GetController());
	if (!TankPlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not get Player Controller!"));
	}

	LevelComponent = Cast<ULevelComponent>(GetComponentByClass(ULevelComponent::StaticClass()));
	if (LevelComponent)
	{
		LevelComponent->OnLevelUp.AddDynamic(this, &ATank::OnLevelUp);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Could not get Level Component!"));
	}
}

void ATank::OnLevelUp(int32 NewLevel)
{
	if (HealthComponent)
	{
		HealthComponent->UpgradeMaxHealthForLevel(NewLevel);
	}
}


float ATank::GetProjectileDamage()
{
	if (LevelComponent)
	{
		return LevelComponent->GetProjectileDamage();
	}

	return 0.f;
}


void ATank::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TankPlayerController)
	{
		FHitResult HitResult;
		TankPlayerController->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility,
			false,
			HitResult
		);

		RotateTurret(HitResult.ImpactPoint);
	}
}

void ATank::HandleDestroyedEnemy(int32 ProvidedXP)
{
	if (LevelComponent)
	{
		LevelComponent->AddXP(ProvidedXP);
	}
}


void ATank::HandleDestruction()
{
	Super::HandleDestruction();

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);

	bAlive = false;
}

void ATank::Move(const float Value)
{
	FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value)
{
	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(DeltaRotation, true);
}
