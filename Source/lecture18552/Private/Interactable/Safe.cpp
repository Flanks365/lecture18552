// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable/Safe.h"

#include "Components/SkeletalMeshComponent.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"

// Sets default values
ASafe::ASafe()
{
	BaseMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;
	
	LootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LootMesh"));
	LootMesh->SetupAttachment(RootComponent);
}

void ASafe::Interact(UPrimitiveComponent* HitComponent)
{
	if (HitComponent == LootMesh)
	{
		CollectLoot();
	}
	else if (HitComponent == BaseMesh)
	{
		Open();
	}
}

void ASafe::Open()
{
	if (BaseMesh)
	{
		// Do something to open the safe, e.g., play an animation
		BaseMesh->Play(false);
	}
	
	BaseMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
}

void ASafe::CollectLoot()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("Loot collected!"));
	}
}



