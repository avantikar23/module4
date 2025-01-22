// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Enemy.h"

void AToonTanksGameMode::ActorDied(AActor *DeadActor)
{
    if (DeadActor == Tank)
    {
        Tank->HandleDestruction();
        if (Tank->GetPlayerController())
        {
            Tank->DisableInput(Tank->GetPlayerController());
            Tank->GetPlayerController()->bShowMouseCursor = true;
            GameOver(false);
        }
    }
    else if (AEnemy* DestroyedEnemy = Cast<AEnemy>(DeadActor))
    {
        DestroyedEnemy->HandleDestruction();
        Count--;
        if(Count==0)
        {
            GameOver(true);
        }
    }
}

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();
    Count = EnemyCount();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

int AToonTanksGameMode::EnemyCount()
{
    TArray<AActor*> Enemies;
    UGameplayStatics:: GetAllActorsOfClass(this,AEnemy::StaticClass(),Enemies);
    return Enemies.Num();
}