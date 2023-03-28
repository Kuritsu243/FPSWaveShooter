// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradeManager.h"

#include "FPSWaveShooterGameMode.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AUpgradeManager::AUpgradeManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUpgradeManager::BeginPlay()
{
	Super::BeginPlay();
	Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	UpgradeModifier = Player->FindComponentByClass<UUpgradeModifier>();
	GameModeBase = UGameplayStatics::GetGameMode(GetWorld());
	CurrentGameMode = Cast<AFPSWaveShooterGameMode>(GameModeBase);
}

// Called every frame
void AUpgradeManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUpgradeManager::RandomizeUpgrades(EPlayerUpgrade& A, EPlayerUpgrade& B, EPlayerUpgrade& C)
{
	A = ReturnRandomUpgrade();
	do
		B = ReturnRandomUpgrade();
	while (B == A);

	do
		C = ReturnRandomUpgrade();
	while (C == B || C == A);
	

}

EPlayerUpgrade AUpgradeManager::ReturnRandomUpgrade()
{
	const int NumOfUpgrades = PlayerUpgrades.Num();
	const int RandomIndex = FMath::RandRange(0, NumOfUpgrades-1);
	return PlayerUpgrades[RandomIndex];
}

void AUpgradeManager::SetRandomizedUpgrades(EPlayerUpgrade Upgrade1, EPlayerUpgrade Upgrade2, EPlayerUpgrade Upgrade3)
{
	RandomUpgrade1 = Upgrade1;
	RandomUpgrade2 = Upgrade2;
	RandomUpgrade3 = Upgrade3;
}


void AUpgradeManager::UpdateButtonNames(FText& Button1Text, FText& Button2Text, FText& Button3Text)
{
	Button1Text = UEnum::GetDisplayValueAsText(RandomUpgrade1);
	Button2Text = UEnum::GetDisplayValueAsText(RandomUpgrade2);
	Button3Text = UEnum::GetDisplayValueAsText(RandomUpgrade3);
}

void AUpgradeManager::UpgradeOneChosen()
{
	switch (RandomUpgrade1)
	{
	case EPlayerUpgrade::HealthUpgrade:
		UpgradeModifier->HealthUpgradeCount++;
		UpgradeModifier->UpgradeHealth();
		CurrentGameMode->UpgradeChosen();
		break;
	case EPlayerUpgrade::SpeedUpgrade:
		UpgradeModifier->SpeedUpgradeCount++;
		UpgradeModifier->UpgradeSpeed();
		CurrentGameMode->UpgradeChosen();
		break;
	case EPlayerUpgrade::DamageUpgrade:
		UpgradeModifier->DamageUpgradeCount++;
		CurrentGameMode->UpgradeChosen();
		break;
	case EPlayerUpgrade::HealthRestore:
		UpgradeModifier->HealthRestoreCount++;
		UpgradeModifier->RestoreHealth();
		CurrentGameMode->UpgradeChosen();
		break;
	case EPlayerUpgrade::FireRateUpgrade:
		UpgradeModifier->FireRateUpgradeCount++;
		UpgradeModifier->IncreaseFireRate();
		CurrentGameMode->UpgradeChosen();
		break;
	default: ;
	}
}

void AUpgradeManager::UpgradeTwoChosen()
{
	switch (RandomUpgrade2)
	{
	case EPlayerUpgrade::HealthUpgrade:
		UpgradeModifier->HealthUpgradeCount++;
		UpgradeModifier->UpgradeHealth();
		CurrentGameMode->UpgradeChosen();
		break;
	case EPlayerUpgrade::SpeedUpgrade:
		UpgradeModifier->SpeedUpgradeCount++;
		UpgradeModifier->UpgradeSpeed();
		CurrentGameMode->UpgradeChosen();
		break;
	case EPlayerUpgrade::DamageUpgrade:
		UpgradeModifier->DamageUpgradeCount++;
		CurrentGameMode->UpgradeChosen();
		break;
	case EPlayerUpgrade::HealthRestore:
		UpgradeModifier->HealthRestoreCount++;
		UpgradeModifier->RestoreHealth();
		CurrentGameMode->UpgradeChosen();
		break;
	case EPlayerUpgrade::FireRateUpgrade:
		UpgradeModifier->FireRateUpgradeCount++;
		UpgradeModifier->IncreaseFireRate();
		CurrentGameMode->UpgradeChosen();
		break;
	default: ;
	}
}

void AUpgradeManager::UpgradeThreeChosen()
{
	switch (RandomUpgrade3)
	{
	case EPlayerUpgrade::HealthUpgrade:
		UpgradeModifier->HealthUpgradeCount++;
		UpgradeModifier->UpgradeHealth();
		CurrentGameMode->UpgradeChosen();
		break;
	case EPlayerUpgrade::SpeedUpgrade:
		UpgradeModifier->SpeedUpgradeCount++;
		UpgradeModifier->UpgradeSpeed();
		CurrentGameMode->UpgradeChosen();
		break;
	case EPlayerUpgrade::DamageUpgrade:
		UpgradeModifier->DamageUpgradeCount++;
		CurrentGameMode->UpgradeChosen();
		break;
	case EPlayerUpgrade::HealthRestore:
		UpgradeModifier->HealthRestoreCount++;
		UpgradeModifier->RestoreHealth();
		CurrentGameMode->UpgradeChosen();
		break;
	case EPlayerUpgrade::FireRateUpgrade:
		UpgradeModifier->FireRateUpgradeCount++;
		UpgradeModifier->IncreaseFireRate();
		CurrentGameMode->UpgradeChosen();
		break;
	default: ;
	}
}


