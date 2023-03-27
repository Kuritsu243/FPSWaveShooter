// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSWaveShooterGameMode.h"
#include "FPSWaveShooterCharacter.h"
#include "WaveSpawner.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AFPSWaveShooterGameMode::AFPSWaveShooterGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;


	

}

void AFPSWaveShooterGameMode::BeginPlay()
{
	Super::BeginPlay();
	GameInstance = GetGameInstance();
	// WidgetBlueprintLibrary = UWidgetBlueprintLibrary::get;
	WaveNo = 1;
	EnemiesDefeatedTotal = 0;
	EnemiesDefeatedThisWave = 0;
	TArray<AActor*> Results;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AWaveSpawner::StaticClass(), FName("WaveSpawnerObject"), Results);
	if (Results.Num() == 0) return; 
	WaveObject = Results[0];
	WaveSpawner = Cast<AWaveSpawner>(WaveObject);

}


void AFPSWaveShooterGameMode::ProgressWave()
{
	EnemiesDefeatedThisWave = 0;
	WaveNo++;
	EnemiesRequiredToAdvance += IncreaseInEnemiesPerWave;
	WaveSpawner->AppendSpawnPoints(NewSpawnsPerWave);
	WaveSpawner->NoToSpawn += IncreaseInEnemiesPerWave;
	NewSpawnsPerWave += IncreaseInSpawnsPerWave;
	NewWaveSteps.Broadcast();
}

void AFPSWaveShooterGameMode::EnemyDefeated()
{
	EnemiesDefeatedTotal++;
	EnemiesDefeatedThisWave++;
	if (EnemiesDefeatedThisWave >= EnemiesRequiredToAdvance)
	{
		ProgressWave();
	}
}

int AFPSWaveShooterGameMode::RandomUpgradeIndex()
{
// 	auto Count =
	return 0;
}

void AFPSWaveShooterGameMode::ShowUpgradesUI()
{
	UpgradesUI = CreateWidget(GetWorld(), UpgradesUIClass);
	UpgradesUI->AddToViewport();
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	UGameplayStatics::GetPlayerCharacter(this, 0);
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
}

void AFPSWaveShooterGameMode::UpgradeChosen()
{
	UpgradesUI->RemoveFromViewport();
	GameplayUI = CreateWidget(GetWorld(), GameplayUIClass);
	GameplayUI->AddToViewport();
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	UGameplayStatics::GetPlayerCharacter(this, 0);

	
}
