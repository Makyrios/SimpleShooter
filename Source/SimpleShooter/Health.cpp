// Fill out your copyright notice in the Description page of Project Settings.


#include "Health.h"
#include "ShooterCharacter.h"
#include "Components/CapsuleComponent.h"
#include "SimpleShooterGameModeBase.h"

// Sets default values for this component's properties
UHealth::UHealth()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealth::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealth::OnTakeDamage);
	
}


// Called every frame
void UHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UHealth::GetHealth() const
{
	return Health;
}

float UHealth::GetHealthPercent() const
{
	return Health / MaxHealth;
}

void UHealth::OnTakeDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser)
{
	Health -= Damage;

	AShooterCharacter* Owner = Cast<AShooterCharacter>(DamageActor);

	if (!Owner)
	{
		return;
	}

	if (Owner->IsDead())
	{
		ASimpleShooterGameModeBase* Gamemode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
		if (Gamemode)
		{
			Gamemode->PawnKilled(Owner);
		}
		Owner->DetachFromControllerPendingDestroy();
		Owner->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);

}

