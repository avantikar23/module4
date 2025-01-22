// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABase
{
	GENERATED_BODY()

public:
 	ATank();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UPROPERTY(EditAnywhere)
	float speed = 100;
	UPROPERTY(EditAnywhere)
	float turnspeed = 100;
	void HandleDestruction();
	APlayerController* GetPlayerController() const { return PlayerController; }


protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere,Category = "Component")
	class USpringArmComponent* SpringArm; 
	UPROPERTY(VisibleAnywhere,Category = "Component")
	class UCameraComponent* Camera;
	void Move(float Value);
	void Turn(float Value);
	void Turret(float Value);
	APlayerController* PlayerController;
};
