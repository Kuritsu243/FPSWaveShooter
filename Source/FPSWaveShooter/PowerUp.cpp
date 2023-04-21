// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUp.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
APowerUp::APowerUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));
	// SphereMesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Engine/BasicShapes/Sphere.Sphere")).Object);
	// RootComponent = SphereMesh;

	// SphereMaterial = UMaterialInstanceDynamic::Create(SphereMesh->GetMaterial(0), nullptr);

}


// Called when the game starts or when spawned
void APowerUp::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	PlayerActor = Cast<AActor>(PlayerPawn);
	PowerUpCollider = FindComponentByClass<UStaticMeshComponent>();
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APowerUpController::StaticClass(), FoundActors);
	if (FoundActors.Num() > 0)
		PowerUpController = Cast<APowerUpController>(FoundActors[0]);

	if (PowerUpCollider)
	{
		PowerUpCollider->OnComponentBeginOverlap.AddDynamic(this, &APowerUp::OnBeginOverlap);
	}
	
	// GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("Powerup: %d"), ReturnRandomPowerup()));
	// FTimerDelegate PowerUpTimerDelegate;
	// GetWorld()->GetTimerManager().SetTimer(PowerUpTimer, this, &APowerUp::DisableAllEnemyMovement, 5.0f, false);
	//
	// SphereMaterial->SetVectorParameterValue(TEXT("Colour"), FLinearColor::Red);
	// SphereMaterial->SetScalarParameterValue(TEXT("base opacity"), 0.5f);
	// SphereMesh->SetMaterial(0, SphereMaterial);

	



}

// Called every frame
void APowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//
	// auto RotationRate = FRotator(0.0f, SpinRate * DeltaTime, 0.0f);
	// PowerUpCollider->AddWorldRotation(RotationRate);
}


EPowerUp APowerUp::ReturnRandomPowerup()
{
	const int NumOfPowerups = PowerUps.Num();
	const int RandomIndex = FMath::RandRange(0, NumOfPowerups-1);
	return PowerUps[RandomIndex];
}

void APowerUp::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == PlayerActor)
	{
		PowerUpController->ActivatePowerUp(ReturnRandomPowerup());
		this->Destroy();
	}



}
