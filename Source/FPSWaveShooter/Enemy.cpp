// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "PlayerHealthComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	PlayerHealthComponent = Player->FindComponentByClass<UPlayerHealthComponent>();
	EnemyMesh = FindComponentByClass<UStaticMeshComponent>();
	bCanDamage = true;
	EnemyMesh->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnBeginOverlap);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveToPlayer();
}

void AEnemy::MoveToPlayer()
{
	if (!Player) return;

	PlayerLocation = Player->GetActorLocation();
	EnemyPos = GetActorLocation();
	DirToPlayer = (PlayerLocation - EnemyPos).GetSafeNormal();
	MoveVector = DirToPlayer * MoveSpeed * GetWorld()->DeltaTimeSeconds;
	MoveVector.Z = 0;

	SetActorLocation(EnemyPos + MoveVector);
}

void AEnemy::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == Player && bCanDamage)
	{
		PlayerHealthComponent->DamagePlayer(DamageAmount);
	}
	StartDamageCooldown();
}

void AEnemy::StartDamageCooldown()
{
	bCanDamage = false;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AEnemy::EndDamageCooldown, DamageCooldown, false);
}

void AEnemy::EndDamageCooldown()
{
	bCanDamage = true;
}

