// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base.h"
#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AEnemy : public ABase
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaTime) override;
	void HandleDestruction();

protected:
	virtual void BeginPlay() override;

private:
	class ATank* Tank;

	FTimerHandle FireRateTimerHandle;
	float FireRate = 2.f;
	void CheckFireCondition();

	bool InFireRange();
};
