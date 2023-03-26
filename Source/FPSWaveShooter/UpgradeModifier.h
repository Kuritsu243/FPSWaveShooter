// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	UPROPERTY(EditAnywhere)
	int HealthUpgradeModifier;
	UPROPERTY(EditAnywhere)
	int SpeedUpgradeModifier;
	UPROPERTY(EditAnywhere)
	int DamageUpgradeModifier;
	UPROPERTY(EditAnywhere)
	int FireRateModifier;

	
	UPROPERTY()
	int HealthUpgradeCount;
	UPROPERTY(BlueprintReadOnly)
	int SpeedUpgradeCount;
	UPROPERTY()
	int DamageUpgradeCount;
	UPROPERTY(BlueprintReadOnly)
	int FireRateUpgradeCount;

	UFUNCTION()
	void RestoreHealth();

	


	
		
};
