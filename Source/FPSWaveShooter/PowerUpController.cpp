// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUpController.h"
#include "Enemy.h"
#include "WaveSpawner.h"
#include "FPSWaveShooterCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APowerUpController::APowerUpController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APowerUpController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APowerUpController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void APowerUpController::DisableAllEnemyMovement()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), FoundEnemies);
	if (FoundEnemies.Num() <= 0) return;
	for (const auto FoundEnemy : FoundEnemies)
		if (const auto EnemyClass = Cast<AEnemy>(FoundEnemy))
			EnemyClass->bCanMove = false;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWaveSpawner::StaticClass(), FoundSpawners);
	if (FoundEnemies.Num() <= 0) return;
	for (const auto FoundSpawner : FoundSpawners)
		if (const auto SpawnerClass = Cast<AWaveSpawner>(FoundSpawner))
			SpawnerClass->bIsEnabled = false;
	
}

void APowerUpController::EnableAllEnemyMovement()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), FoundEnemies);
	if (FoundEnemies.Num() <= 0) return;
	for (const auto FoundEnemy : FoundEnemies)
		if (const auto EnemyClass = Cast<AEnemy>(FoundEnemy))
			EnemyClass->bCanMove = true;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWaveSpawner::StaticClass(), FoundSpawners);
	if (FoundEnemies.Num() <= 0) return;
	for (const auto FoundSpawner : FoundSpawners)
		if (const auto SpawnerClass = Cast<AWaveSpawner>(FoundSpawner))
			SpawnerClass->bIsEnabled = true;
	
}

void APowerUpController::EnableInstantKill() 
{
	Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (const auto PlayerScript = Cast<AFPSWaveShooterCharacter>(Player))
		PlayerScript->bIsInstantKill = true;
}

void APowerUpController::DisableInstantKill()
{
	Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (const auto PlayerScript = Cast<AFPSWaveShooterCharacter>(Player))
		PlayerScript->bIsInstantKill = false;
}

void APowerUpController::EnableRapidFire()
{
	Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (const auto PlayerScript = Cast<AFPSWaveShooterCharacter>(Player))
		PlayerScript->bIsRapidFire = true;
}

void APowerUpController::DisableRapidFire()
{
	Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (const auto PlayerScript = Cast<AFPSWaveShooterCharacter>(Player))
		PlayerScript->bIsRapidFire = false;
}

void APowerUpController::NukeEnemies()
{
	
}

void APowerUpController::ActivatePowerUp(EPowerUp GeneratedPowerup)
{
	switch (GeneratedPowerup)
	{
	case EPowerUp::InstantKill:
		EnableInstantKill();
		PowerUpTimerDelegate = FTimerDelegate::CreateUObject(this, &APowerUpController::DisableInstantKill);
		GetWorld()->GetTimerManager().SetTimer(PowerUpTimer, PowerUpTimerDelegate, InstantKillDuration, false);
		break;
	case EPowerUp::EnemyFreeze:
		DisableAllEnemyMovement();
		PowerUpTimerDelegate = FTimerDelegate::CreateUObject(this, &APowerUpController::EnableAllEnemyMovement);
		GetWorld()->GetTimerManager().SetTimer(PowerUpTimer, PowerUpTimerDelegate, FreezeDuration, false);
		break;
	case EPowerUp::RapidFire:
		EnableRapidFire();
		PowerUpTimerDelegate = FTimerDelegate::CreateUObject(this, &APowerUpController::DisableRapidFire);
		GetWorld()->GetTimerManager().SetTimer(PowerUpTimer, PowerUpTimerDelegate, RapidFireDuration, false);
		break;
	case EPowerUp::Nuke:
		DisableAllEnemyMovement();
		PowerUpTimerDelegate = FTimerDelegate::CreateUObject(this, &APowerUpController::EnableAllEnemyMovement);
		GetWorld()->GetTimerManager().SetTimer(PowerUpTimer, PowerUpTimerDelegate, 2.0f, false);
		break;
	default: ;
	}
}
