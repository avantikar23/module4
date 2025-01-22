// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));
    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &AEnemy::CheckFireCondition, FireRate, true);
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if(Tank)
    {
        if(InFireRange())
        {
            TurretRotate(Tank->GetActorLocation());
        }
    }
}

void AEnemy::HandleDestruction()
{
    Destroy();
}

void AEnemy::CheckFireCondition()
{
    if (Tank == nullptr || Tank -> IsHidden())
    {
        return;
    }
    if (InFireRange())
    {
        Fire();
    }
}

bool AEnemy::InFireRange()
{
    if (Tank)
    {
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
        if (Distance <= 500)
        {
            return true;
        }
    }
        return false;
}
