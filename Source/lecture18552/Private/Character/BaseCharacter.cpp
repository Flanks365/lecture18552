// Fill out your copyright notice in the Description page of Project Settings.


#include "./Character/BaseCharacter.h"
#include "Components/SkeletalMeshComponent.h"



// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

void ABaseCharacter::SpawnProjectile(FName SocketName, TSubclassOf<AProjectile> ProjectileClass)
{
	if (!ProjectileClass || !GetWorld() || !GetMesh()) return;
	
	if (ActiveSpawnedProjectile)
	{
		ActiveSpawnedProjectile->Destroy();
		ActiveSpawnedProjectile = nullptr;
	}
	
	FVector SpawnLocation = GetMesh()->GetSocketLocation(SocketName);
	FRotator SpawnRotation = GetActorRotation();
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	ActiveSpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
	
	if (ActiveSpawnedProjectile && ActiveSpawnedProjectile->ProjectileMovement)
	{
		ActiveSpawnedProjectile->ProjectileMovement->InitialSpeed = 0.0f;
		ActiveSpawnedProjectile->ProjectileMovement->Velocity = FVector::ZeroVector;
	}
	
	FAttachmentTransformRules AttachRules(
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::KeepRelative,
		false);
	
	ActiveSpawnedProjectile->AttachToComponent(GetMesh(), AttachRules, SocketName);
}

void ABaseCharacter::LaunchProjectile()
{
	if (ActiveSpawnedProjectile && ActiveSpawnedProjectile->ProjectileMovement)
	{
		FDetachmentTransformRules DetachRules(EDetachmentRule::KeepWorld, true);
		
		ActiveSpawnedProjectile->DetachFromActor(DetachRules);
		
		ActiveSpawnedProjectile->ProjectileMovement->ProjectileGravityScale = ActiveSpawnedProjectile->LaunchGravityScale;
		
		FVector LaunchDirection = GetActorForwardVector();
		float launchSpeed = ActiveSpawnedProjectile->ProjectileMovement->MaxSpeed;
		
		ActiveSpawnedProjectile->ProjectileMovement->Velocity = (LaunchDirection * launchSpeed) + GetVelocity();
		
		ActiveSpawnedProjectile->SetActorRotation(GetActorRotation());
		
		ActiveSpawnedProjectile = nullptr;
		
	}
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


