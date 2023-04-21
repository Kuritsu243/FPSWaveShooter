// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerUpController.generated.h"

UENUM()
enum class EPowerUp : uint8
{
	InstantKill,
	EnemyFreeze,
	RapidFire,
	Nuke
};



UCLASS()
class FPSWAVESHOOTER_API APowerUpController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerUpController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	UPROPERTY(EditAnywhere)
	TArray<EPowerUp> PowerUps =
	{
		EPowerUp::InstantKill,
		EPowerUp::EnemyFreeze,
		EPowerUp::RapidFire,
		EPowerUp::Nuke
	};

	UFUNCTION()
	void DisableAllEnemyMovement();
	UFUNCTION()
	void EnableAllEnemyMovement();
	UFUNCTION()
	void EnableInstantKill();
	UFUNCTION()
	void DisableInstantKill();
	UFUNCTION()
	void EnableRapidFire();
	UFUNCTION()
	void DisableRapidFire();
	UFUNCTION()
	void NukeEnemies();

	UFUNCTION()
	void ActivatePowerUp(EPowerUp GeneratedPowerup);



	UPROPERTY(EditAnywhere)
	float FreezeDuration;
	UPROPERTY(EditAnywhere)
	float RapidFireDuration;
	UPROPERTY(EditAnywhere)
	float InstantKillDuration;
	UPROPERTY()
	FTimerHandle PowerUpTimer;
	FTimerDelegate PowerUpTimerDelegate;
	UPROPERTY()
	bool bCanPickupPowerup;
	UPROPERTY()
	UStaticMeshComponent* SphereMesh;
	UPROPERTY()
	UMaterialInstanceDynamic* SphereMaterial;
	UPROPERTY()
	TArray<AActor*> FoundEnemies;
	UPROPERTY()
	TArray<AActor*> FoundSpawners;
	UPROPERTY()
	ACharacter* Player;
};
