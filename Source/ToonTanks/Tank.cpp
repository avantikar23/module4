// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

void ATank::BeginPlay()
{
    PlayerController = Cast<APlayerController>(GetController());
	Super::BeginPlay();
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if(PlayerController)
    {
        FHitResult HitResult;
        PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,false,HitResult);
        TurretRotate(HitResult.ImpactPoint);
    }
}
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis(TEXT("Forward"),this,&ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"),this,&ATank::Turn);
    PlayerInputComponent->BindAction(TEXT("Fire"),IE_Pressed, this, &ATank::Fire);
}

void ATank::Move(float Value)
{
    FVector DeltaLocation = FVector(Value*speed*GetWorld()->GetDeltaSeconds(),0,0);
    AddActorLocalOffset(DeltaLocation,true);
}

void ATank::Turn(float Value)
{
    FRotator DeltaRotation = FRotator::ZeroRotator;
    DeltaRotation.Yaw = Value*turnspeed*UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalRotation(DeltaRotation,true);
}

void ATank::HandleDestruction()
{
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
}

// void ATank::Turret(float Value)
// {
//     FRotator DeltaRotation = FRotator::ZeroRotator;
//     DeltaRotation.Yaw = Value*turnspeed*UGameplayStatics::GetWorldDeltaSeconds(this);
//     ABase::Turret -> AddWorldRotation(DeltaRotation,true);
// }