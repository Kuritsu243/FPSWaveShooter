// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHealthComponent.h"

#include "FPSWaveShooterGameMode.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UPlayerHealthComponent::UPlayerHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UPlayerHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	// ...

}

void UPlayerHealthComponent::DamagePlayer(float DamageAmount)
{
	CurrentHealth -= DamageAmount;

	if (CurrentHealth<= 0)
	{
		const auto GameMode = UGameplayStatics::GetGameMode(GetWorld());
		if (!GameMode) return;
		const auto GameModeClass = Cast<AFPSWaveShooterGameMode>(GameMode);
		if (!GameModeClass) return;
		if (GameModeClass->bIsPlayerDead) return;
		// PlayerDeathEvent.Broadcast();
		GameModeClass->PlayerDeath();
	}
}


// Called every frame
void UPlayerHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


