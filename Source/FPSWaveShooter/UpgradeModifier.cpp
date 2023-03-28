// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradeModifier.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UUpgradeModifier::UUpgradeModifier()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UUpgradeModifier::BeginPlay()
{
	Super::BeginPlay();
	Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	PlayerHealth = Player->FindComponentByClass<UPlayerHealthComponent>();
	SpeedUpgradeBaseVal = SpeedUpgradeModifier;
	DamageUpgradeBaseVal = DamageUpgradeModifier;
	FireRateBaseVal = FireRateModifier;

	SpeedUpgradeModifier = 0.0f;
	DamageUpgradeModifier = 0.0f;
	// ...
	
}


// Called every frame
void UUpgradeModifier::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UUpgradeModifier::RestoreHealth() const
{
	if (PlayerHealth->CurrentHealth + HealthRestoreAmount >= PlayerHealth->MaxHealth)
		PlayerHealth->CurrentHealth = PlayerHealth->MaxHealth;
	else
		PlayerHealth->CurrentHealth += HealthRestoreAmount;
}

void UUpgradeModifier::UpgradeHealth() const
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Max Health: %d"), PlayerHealth->MaxHealth));
	PlayerHealth->MaxHealth += HealthUpgradeModifier;
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Max Upgraded Health: %d"), PlayerHealth->MaxHealth));
	PlayerHealth->CurrentHealth += HealthUpgradeModifier;
}

void UUpgradeModifier::UpgradeSpeed() 
{
	SpeedUpgradeModifier += SpeedUpgradeBaseVal;
}

void UUpgradeModifier::IncreaseFireRate()
{
	if (TimeBetweenShots >= 0.05 && TimeBetweenShots - FireRateModifier >= 0.05)
	{
		TimeBetweenShots -= FireRateModifier;
	}
	else
	{
		TimeBetweenShots = 0.05f;
	}
}


