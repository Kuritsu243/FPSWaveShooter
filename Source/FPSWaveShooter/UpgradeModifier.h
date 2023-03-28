// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerHealthComponent.h"
#include "Components/ActorComponent.h"
#include "UpgradeModifier.generated.h"




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSWAVESHOOTER_API UUpgradeModifier : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUpgradeModifier();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int HealthRestoreAmount;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int HealthUpgradeModifier;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpeedUpgradeModifier;
	UPROPERTY(EditAnywhere, BlueprintReadOnly);
	int DamageUpgradeModifier;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float FireRateModifier;

	
	UPROPERTY(BlueprintReadOnly)
	int HealthUpgradeCount;
	UPROPERTY(BlueprintReadOnly)
	int SpeedUpgradeCount;
	UPROPERTY(BlueprintReadOnly)
	int DamageUpgradeCount;
	UPROPERTY(BlueprintReadOnly)
	int FireRateUpgradeCount;
	UPROPERTY(BlueprintReadOnly)
	int HealthRestoreCount;

	
	UPROPERTY()
	float SpeedUpgradeBaseVal;
	UPROPERTY()
	float DamageUpgradeBaseVal;
	UPROPERTY()
	float FireRateBaseVal;
	UPROPERTY(EditAnywhere)
	float TimeBetweenShots = 0.35f;
	
	UFUNCTION()
	void RestoreHealth() const;
	UFUNCTION()
	void UpgradeHealth() const;
	UFUNCTION()
	void UpgradeSpeed();
	UFUNCTION()
	void IncreaseFireRate();

	

	UPROPERTY()
	ACharacter* Player;
	UPROPERTY()
	UPlayerHealthComponent* PlayerHealth;
	


	
		
};
