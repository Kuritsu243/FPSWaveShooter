// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UpgradeModifier.h"
#include "GameFramework/Actor.h"
#include "UpgradeManager.generated.h"

UENUM()
enum class EPlayerUpgrade : uint8
{
	HealthUpgrade,
	SpeedUpgrade,
	DamageUpgrade,
	HealthRestore,
	FireRateUpgrade
};


UCLASS()
class FPSWAVESHOOTER_API AUpgradeManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUpgradeManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TArray<EPlayerUpgrade> PlayerUpgrades =
	{
		EPlayerUpgrade::DamageUpgrade,
		EPlayerUpgrade::HealthRestore,
		EPlayerUpgrade::HealthUpgrade,
		EPlayerUpgrade::SpeedUpgrade,
		EPlayerUpgrade::FireRateUpgrade
	};
	
	UPROPERTY()
	ACharacter* Player;
	UPROPERTY()
	UUpgradeModifier* UpgradeModifier;
	

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPlayerUpgrade RandomUpgrade1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPlayerUpgrade RandomUpgrade2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPlayerUpgrade RandomUpgrade3;

	UFUNCTION(BlueprintCallable)
	void RandomizeUpgrades(EPlayerUpgrade& A, EPlayerUpgrade& B, EPlayerUpgrade& C);

		
	UFUNCTION(BlueprintCallable)
	EPlayerUpgrade ReturnRandomUpgrade();

	UFUNCTION(BlueprintCallable)
	void SetRandomizedUpgrades(EPlayerUpgrade Upgrade1, EPlayerUpgrade Upgrade2, EPlayerUpgrade Upgrade3);

	
	UFUNCTION(BlueprintCallable)
	void UpdateButtonNames(FText& Button1Text, FText& Button2Text, FText& Button3Text);

	UFUNCTION(BlueprintCallable)
	void UpgradeOneChosen();
	
	UFUNCTION(BlueprintCallable)
	void UpgradeTwoChosen();
	
	UFUNCTION(BlueprintCallable)
	void UpgradeThreeChosen();	
};
