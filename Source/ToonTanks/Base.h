// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Base.generated.h"

UCLASS()
class TOONTANKS_API ABase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABase();

protected:
	// Called when the game starts or when spawned
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Meta = (AllowPrivateAccess ="true"))
	UStaticMeshComponent* Turret;
	void Fire();
	UPROPERTY(EditAnyWhere)
	TSubclassOf<class AProjectile> ProjectileClass;

private:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Meta = (AllowPrivateAccess ="true"))
	class UCapsuleComponent* Capsule;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Meta = (AllowPrivateAccess ="true"))
	UStaticMeshComponent* Base;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Meta = (AllowPrivateAccess ="true"))
	USceneComponent* Offset;
public:	
	// Called every frame
	void TurretRotate(FVector TargetPoint);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
