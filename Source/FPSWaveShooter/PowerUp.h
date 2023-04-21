// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUpController.h"
#include "GameFramework/Actor.h"
#include "PowerUp.generated.h"




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

	
	UFUNCTION()
	EPowerUp ReturnRandomPowerup();

	
	UPROPERTY(EditAnywhere)
	TArray<EPowerUp> PowerUps =
	{
		EPowerUp::InstantKill,
		EPowerUp::EnemyFreeze,
		EPowerUp::RapidFire,
		EPowerUp::Nuke
	};

	UPROPERTY(EditAnywhere)
	float SpinRate;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	
	UPROPERTY()
	APowerUpController* PowerUpController;
	UPROPERTY()
	UStaticMeshComponent* PowerUpCollider;

	UPROPERTY()
	APawn* PlayerPawn;
	UPROPERTY()
	AActor* PlayerActor;

};
