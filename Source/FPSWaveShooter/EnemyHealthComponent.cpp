// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyHealthComponent.h"

#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UEnemyHealthComponent::UEnemyHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UEnemyHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	EnemyCurrentHealth = EnemyMaxHealth;
	EnemyActor = GetOwner();

	WaveGameModeBase = UGameplayStatics::GetGameMode(GetWorld());
	WaveGameMode = Cast<AFPSWaveShooterGameMode>(WaveGameModeBase);
	
	
}



void UEnemyHealthComponent::TakeDamage(int DamageAmount)
{
	EnemyCurrentHealth -= DamageAmount;
	if (EnemyCurrentHealth <= 0.0)
		Die();
}

void UEnemyHealthComponent::Die() const
{
	WaveGameMode->EnemyDefeated();
	EnemyActor->Destroy();
}





void UEnemyHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



