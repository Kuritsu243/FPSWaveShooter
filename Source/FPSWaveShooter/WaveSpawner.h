// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UpgradeModifier.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Actor.h"
#include "WaveSpawner.generated.h"




UCLASS()
class FPSWAVESHOOTER_API AWaveSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaveSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// wave spawning
	UPROPERTY(EditAnywhere)
	TArray<ATargetPoint*> SpawnPoints;
	UPROPERTY(EditAnywhere)
	float SpawnTime;
	UPROPERTY(EditAnywhere)
	int NoToSpawn;
	UPROPERTY(EditAnywhere)
	int NoOfPoints;
	UPROPERTY(EditAnywhere)
	bool bIsEnabled;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> EnemyClass;
	UPROPERTY(EditAnywhere)
	float MinDistToPlayer;
	UPROPERTY(EditAnywhere)
	ATargetPoint* ChosenPoint = nullptr;
	UPROPERTY(EditAnywhere)
	ACharacter* Player;

	// enemy spawning
	UPROPERTY()
	FTimerHandle TimerHandle;
	UFUNCTION()
	void SpawnEnemies();
	// random location
	UFUNCTION()
	ATargetPoint* RandomizeSpawn();

	// random location boundary calculation
	UFUNCTION()
	void SetBounds();

	UPROPERTY(EditAnywhere)
	AActor* Floor;
	UPROPERTY()
	UStaticMesh* FloorMesh;
	UPROPERTY()
	FBoxSphereBounds FloorBounds;
	UPROPERTY()
	FVector FloorScale;
	UPROPERTY()
	FVector RandomPos;


	// spawn point generation and randomization
	UFUNCTION()
	void InitSpawnPoints();
	UFUNCTION()
	FVector NewSpawnLocation();
	UFUNCTION()
	void GenNewLocations();
	UFUNCTION()
	void AppendSpawnPoints(int Amount);
	UFUNCTION()
	FVector GetPosWithinBounds(FVector Box) const;







};
