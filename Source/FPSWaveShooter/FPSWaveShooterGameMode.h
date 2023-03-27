// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/GameModeBase.h"
#include "FPSWaveShooterGameMode.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNewWave);

UENUM()
enum EWaveUpgrades
{
	RestoreHealth UMETA(DisplayName="Restore Health"),
	IncDamage UMETA(DisplayName="Increased Damage"),
	IncHealth UMETA(DisplayName="Increased Health"),
	IncFireRate UMETA(DisplayName="Faster Fire-rate")
};


class AWaveSpawner;
UCLASS(minimalapi)
class AFPSWaveShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	
public:
	AFPSWaveShooterGameMode();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int EnemiesRequiredToAdvance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int IncreaseInRequirementEachWave;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int WaveNo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NewSpawnsPerWave;
	UPROPERTY(EditAnywhere)
	int IncreaseInSpawnsPerWave;
	UPROPERTY(EditAnywhere)
	int IncreaseInEnemiesPerWave;
	UPROPERTY(BlueprintReadWrite)
	int EnemiesDefeatedTotal;
	UPROPERTY(BlueprintReadWrite)
	int EnemiesDefeatedThisWave;

	UPROPERTY()
	AActor* WaveObject;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AWaveSpawner* WaveSpawner;

	UFUNCTION()
	void ProgressWave();
	UFUNCTION()
	void EnemyDefeated();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EWaveUpgrades> Upgrades;

	UFUNCTION(BlueprintCallable)
	int RandomUpgradeIndex();

	UPROPERTY(EditAnywhere, BlueprintAssignable)
	FNewWave NewWaveSteps;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> UpgradesUIClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> GameplayUIClass;
	
	UPROPERTY()
	UUserWidget* UpgradesUI;

	UPROPERTY()
	UUserWidget* GameplayUI;
	
	UFUNCTION(BlueprintCallable)
	void ShowUpgradesUI();

	UFUNCTION(BlueprintCallable)
	void UpgradeChosen();


	UPROPERTY()
	UGameInstance* GameInstance;


	

};



