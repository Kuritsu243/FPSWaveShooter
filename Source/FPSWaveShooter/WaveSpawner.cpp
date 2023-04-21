// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveSpawner.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
AWaveSpawner::AWaveSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



}

// Called when the game starts or when spawned
void AWaveSpawner::BeginPlay()
{
	Super::BeginPlay();

	if (!bIsEnabled) return; 
	SetBounds();
	InitSpawnPoints();
	GenNewLocations();
	// UpgradeGenerator = Cast<UUpgradeModifier>(Player);
	//
	GetGameInstance()->TimerManager->SetTimer(TimerHandle, this, &AWaveSpawner::SpawnEnemies, SpawnTime, true);
}

// Called every frame
void AWaveSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWaveSpawner::SpawnEnemies()
{
	if (!bIsEnabled) return;
	// GenNewLocations();
	for (auto i = 0; i <= NoToSpawn; i++)
	{
		GenNewLocations();
		ChosenPoint = RandomizeSpawn();
		auto PointLocation = ChosenPoint->GetActorLocation();
		auto PointRotation = ChosenPoint->GetActorRotation();
		auto EnemyInstance = GetWorld()->SpawnActor<AActor>(EnemyClass, PointLocation, PointRotation);
	}
}

ATargetPoint* AWaveSpawner::RandomizeSpawn()
{
	const auto ChosenNum = FMath::RandRange(0, SpawnPoints.Num()-1);
	return SpawnPoints[ChosenNum];
}

void AWaveSpawner::SetBounds()
{
	Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FloorMesh = Floor->FindComponentByClass<UStaticMeshComponent>()->GetStaticMesh();
	FloorBounds = FloorMesh->GetBounds();
	FloorScale = Floor->GetActorScale();
	FloorBounds.BoxExtent *= FloorScale;
}

void AWaveSpawner::InitSpawnPoints()
{
	for (auto j = 0; j <= NoOfPoints; j++)
	{
		ATargetPoint* NewPoint = GetWorld()->SpawnActor<ATargetPoint>(ATargetPoint::StaticClass());
		NewPoint->SetActorLocation(FVector::Zero());
		NewPoint->SetActorRotation(FRotator(0));
		SpawnPoints.Add(NewPoint);
		if (SpawnPoints.Num() == 0) return;
	}
	GenNewLocations();
}

FVector AWaveSpawner::NewSpawnLocation()
{
	auto bHasBeenCalledYet = false;
	do
	{
		bHasBeenCalledYet = true;
		const auto Box = FloorBounds.BoxExtent;
		RandomPos = FloorBounds.Origin + FVector(FMath::FRandRange(-Box.X, Box.X),
			FMath::FRandRange(-Box.Y, Box.Y), 15);
	}
	while (!bHasBeenCalledYet && ((RandomPos - Player->GetActorScale()).Size() < MinDistToPlayer));
	return RandomPos;
}

void AWaveSpawner::GenNewLocations()
{
	if (SpawnPoints.Num() <= 0) return;
	for (int h = 0; h <= SpawnPoints.Num()-1; h++)
	{
		SpawnPoints[h]->SetActorLocation(NewSpawnLocation());
	}
}

void AWaveSpawner::AppendSpawnPoints(int Amount)
{
	if (!Amount == 0) return;
	for (auto k = 0; k < Amount; k++)
	{
		ATargetPoint* NewPoint = GetWorld()->SpawnActor<ATargetPoint>(ATargetPoint::StaticClass());
		NewPoint->SetActorLocation(FVector(0, 0, 50));
		NewPoint->SetActorRotation(FRotator(0));
		SpawnPoints.Add(NewPoint);
		GenNewLocations();
	}
}



