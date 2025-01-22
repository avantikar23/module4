// Fill out your copyright notice in the Description page of Project Settings.


#include "Base.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

// Sets default values
ABase::ABase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = Capsule;
	Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
	Base->SetupAttachment(Capsule);
	Turret= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret"));
	Turret->SetupAttachment(Base);
	Offset = CreateDefaultSubobject<USceneComponent>(TEXT("Offset"));
	Offset->SetupAttachment(Turret);
}

// Called when the game starts or when spawned

// Called every frame
void ABase::TurretRotate(FVector TargetPoint)
{
	FVector ToRotation = TargetPoint - GetActorLocation();
	FRotator ToRotate = FRotator(0,ToRotation.Rotation().Yaw,0);
	Turret->SetWorldRotation(FMath::RInterpTo(Turret->GetComponentRotation(),ToRotate,UGameplayStatics::GetWorldDeltaSeconds(this),10));
}

// Called to bind functionality to input
void ABase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABase::Fire()
{
	FVector Location = Offset->GetComponentLocation();
	FRotator Rotation = Offset->GetComponentRotation();

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
	Projectile->SetOwner(this);
}
