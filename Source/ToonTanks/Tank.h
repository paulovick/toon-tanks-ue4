// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void Tick(float DeltaTime) override;

	void HandleDestroyedEnemy(int32 ProvidedXP);
	void HandleDestruction();

	APlayerController* GetTankPlayerController() const;

	bool bAlive = true;

protected:

	virtual void BeginPlay() override;
	virtual float GetProjectileDamage() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed = 200.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnRate = 45.f;

	void Move(float Value);
	void Turn(float Value);

	APlayerController* TankPlayerController;
	class ULevelComponent* LevelComponent;

	UFUNCTION()
	void OnLevelUp(int32 NewLevel);
};
