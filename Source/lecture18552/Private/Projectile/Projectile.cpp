// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/Projectile.h"

#include "SWarningOrErrorBox.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Engine/World.h"


// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	
	RootComponent = SphereCollider;
	
	//Collision
	SphereCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SphereCollider->SetCollisionResponseToAllChannels(ECR_Block);
	SphereCollider->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	
	ProjectileMovement->InitialSpeed = 2000.0f;
	ProjectileMovement->MaxSpeed = 2000.0f;
	
	ProjectileMovement->ProjectileGravityScale = 0.0f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	SphereCollider->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	SphereCollider->IgnoreActorWhenMoving(GetOwner(), true);
	SetLifeSpan(10.0f);
	
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	
	if (OtherActor && OtherActor != this && OtherActor != GetOwner() && OtherComp)
	{
		float BaseDamage = 25.0f;
		
		if (bApplyRadialDamage)
		{
			TArray<AActor*> ActorsToIgnore;
			
			ActorsToIgnore.Add(this);
			
			if (GetOwner())
			{
				ActorsToIgnore.Add(GetOwner());
			}
			
			UGameplayStatics::ApplyRadialDamage(
				GetWorld(),
				BaseDamage,
				Hit.ImpactPoint,
				1500.0f,
				UDamageType::StaticClass(),
				ActorsToIgnore,
				this,
				GetInstigatorController(),
				false
			);
			
			//play some sound
		} else
		{
			UGameplayStatics::ApplyDamage(
				OtherActor,
				BaseDamage,
				GetInstigatorController(),
				this,
				UDamageType::StaticClass()
			);
		}
		
		Destroy();
		
		
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

