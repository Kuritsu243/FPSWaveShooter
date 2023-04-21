// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUp.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

class UPlayerHealthComponent;
UCLASS()
class FPSWAVESHOOTER_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void MoveToPlayer();
	UPROPERTY(EditAnywhere)
	float MoveSpeed;
	UPROPERTY()
	ACharacter* Player;
	UPROPERTY(EditAnywhere)
	bool bCanMove = true;
	UPROPERTY()
	FVector PlayerLocation;
	UPROPERTY(EditAnywhere)
	float DamageAmount;
	UPROPERTY(EditAnywhere)
	float DamageCooldown;
	UPROPERTY()
	FVector DirToPlayer;
	UPROPERTY()
	FVector EnemyPos;
	UPROPERTY()
	FVector MoveVector;
	UPROPERTY()
	bool bCanDamage;
	UPROPERTY()
	UStaticMeshComponent* EnemyMesh;
	UPROPERTY()
	FTimerHandle TimerHandle;
	UPROPERTY()
	UPlayerHealthComponent* PlayerHealthComponent;
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	UFUNCTION()
	void StartDamageCooldown();
	UFUNCTION()
	void EndDamageCooldown();
	UFUNCTION()
	bool WillDropPowerUp() const;
	UPROPERTY(EditAnywhere)
	int PowerUpChance;
	UPROPERTY(EditAnywhere)
	TSubclassOf<APowerUp> PowerUpClass;
	UFUNCTION()
	void SpawnPowerUp() const;



	



};
