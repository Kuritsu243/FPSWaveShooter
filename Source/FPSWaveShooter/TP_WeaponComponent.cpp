// Copyright Epic Games, Inc. All Rights Reserved.


#include "TP_WeaponComponent.h"
#include "FPSWaveShooterCharacter.h"
#include "FPSWaveShooterProjectile.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"

void UTP_WeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (Character == nullptr) return;
	
	while (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::LeftMouseButton) && !bIsInCooldown)
	{
		// Print a message to the screen
		GEngine->AddOnScreenDebugMessage(-1, 0.2f, FColor::Yellow, TEXT("Left mouse button is being held down!"));

		if (ProjectileClass != nullptr)
		{
			if (UpgradeModifier == nullptr)
			{
				auto Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
				UpgradeModifier = Player->FindComponentByClass<UUpgradeModifier>();
			}
			TimerDelegate = FTimerDelegate::CreateUObject(this, &UTP_WeaponComponent::TimerCooldown);
			UWorld* const World = GetWorld();
			if (World != nullptr)
			{
				APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
				const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
				// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
				const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);
	
				//Set Spawn Collision Handling Override
				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

				if(Character == nullptr || Character->GetController() == nullptr)
				{
					return;
				}


				// Try and fire a projectile
	
	
				// Try and play the sound if specified
				if (FireSound != nullptr)
				{
					UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
				}
	
				// Try and play a firing animation if specified
				if (FireAnimation != nullptr)
				{
					// Get the animation object for the arms mesh
					UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
					if (AnimInstance != nullptr)
					{
						AnimInstance->Montage_Play(FireAnimation, 1.f);
					}
				}
				
				// Spawn the projectile at the muzzle
				SpawnedProjectile = World->SpawnActor<AFPSWaveShooterProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
				bIsInCooldown = true;
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, UpgradeModifier->TimeBetweenShots, false);
			}
		}
		return;
	}
}

void UTP_WeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	
	bHasCollectedWeapon = false;
}

// Sets default values for this component's properties
UTP_WeaponComponent::UTP_WeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	// Default offset from the character location for projectiles to spawn
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);

}


void UTP_WeaponComponent::Fire()
{

}

void UTP_WeaponComponent::TimerCooldown()
{
	bIsInCooldown = false;
}

void UTP_WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if(Character != nullptr)
	{
		// Unregister from the OnUseItem Event
		Character->OnUseItem.RemoveDynamic(this, &UTP_WeaponComponent::Fire);
	}
}


void UTP_WeaponComponent::AttachWeapon(AFPSWaveShooterCharacter* TargetCharacter)
{
	Character = TargetCharacter;
	if(Character != nullptr)
	{
		// Attach the weapon to the First Person Character
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
		GetOwner()->AttachToComponent(Character->GetMesh1P(),AttachmentRules, FName(TEXT("GripPoint")));

		// Register so that Fire is called every time the character tries to use the item being held
		Character->OnUseItem.AddDynamic(this, &UTP_WeaponComponent::Fire);
	}
}

