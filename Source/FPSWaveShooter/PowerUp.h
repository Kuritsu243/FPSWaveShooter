// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "PowerUp.generated.h"



UENUM()
enum class EPowerUp : uint8
{
	InstantKill,
	EnemyFreeze,
	RapidFire,
	Nuke
};

UCLASS()
class FPSWAVESHOOTER_API APowerUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerUp();

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
	EPowerUp ReturnRandomPowerup();
	UFUNCTION()
	void DisableAllEnemyMovement();
	UFUNCTION()
	void EnableAllEnemyMovement();
	UPROPERTY(EditAnywhere)
	float FreezeDuration;
	UPROPERTY(EditAnywhere)
	float RapidFireDuration;
	UPROPERTY()
	FTimerHandle PowerUpTimer;
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

};
