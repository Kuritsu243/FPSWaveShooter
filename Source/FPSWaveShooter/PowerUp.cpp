// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUp.h"

#include "Enemy.h"
#include "WaveSpawner.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APowerUp::APowerUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));
	SphereMesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Engine/BasicShapes/Sphere.Sphere")).Object);
	RootComponent = SphereMesh;

	// SphereMaterial = UMaterialInstanceDynamic::Create(SphereMesh->GetMaterial(0), nullptr);

}


// Called when the game starts or when spawned
void APowerUp::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("Powerup: %d"), ReturnRandomPowerup()));
	FTimerDelegate PowerUpTimerDelegate;
	GetWorld()->GetTimerManager().SetTimer(PowerUpTimer, this, &APowerUp::DisableAllEnemyMovement, 5.0f, false);
	
	// SphereMaterial->SetVectorParameterValue(TEXT("Colour"), FLinearColor::Red);
	// SphereMaterial->SetScalarParameterValue(TEXT("base opacity"), 0.5f);
	// SphereMesh->SetMaterial(0, SphereMaterial);



}

// Called every frame
void APowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

EPowerUp APowerUp::ReturnRandomPowerup()
{
	const int NumOfPowerups = PowerUps.Num();
	const int RandomIndex = FMath::RandRange(0, NumOfPowerups-1);
	return PowerUps[RandomIndex];
}

void APowerUp::DisableAllEnemyMovement()
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

void APowerUp::EnableAllEnemyMovement()
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

