// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;
class UHealth;

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	void Shoot();


private:
	UPROPERTY(EditAnywhere, Category = "Movement")
	float RotationRate = 10;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<AGun> GunClass;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<UHealth> HealthClass;

	UPROPERTY()
	AGun* Gun;

	UCapsuleComponent* CapsuleCollider;

	UHealth* HealthComponent;


	void SpawnGun();

	void MoveForward(float AxisValue);
	
	void MoveRight(float AxisValue);

	void LookUpRate(float AxisValue);

	void LookRightRate(float AxisValue);

	void ChangeShoulder();

};
