// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSWaveShooterGameMode.h"
#include "Components/ActorComponent.h"
#include "EnemyHealthComponent.generated.h"


class AEnemy;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSWAVESHOOTER_API UEnemyHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
	float EnemyMaxHealth;
	UPROPERTY()
	float EnemyCurrentHealth;
	UPROPERTY()
	AActor* EnemyActor;
	UPROPERTY()
	AGameModeBase* WaveGameModeBase;
	UPROPERTY()
	AFPSWaveShooterGameMode* WaveGameMode;
	UPROPERTY()
	AEnemy* EnemyScript;

	UFUNCTION()
	void TakeDamage(int DamageAmount);

	
	UFUNCTION()
	void Die() const;

		
};
