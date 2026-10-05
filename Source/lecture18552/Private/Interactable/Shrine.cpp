// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable/Shrine.h"

#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "Engine/Engine.h"


// Sets default values
AShrine::AShrine()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;
	
	ShrineLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("ShrineLight"));
	ShrineLight-> SetupAttachment(RootComponent);
	
	ShrineLight->SetVisibility(false);
	bIsActive = false;
}

void AShrine::Interact(UPrimitiveComponent* HitComponent)
{
	Activate();
}

void AShrine::Activate()
{
	
	bIsActive = true;
	
	ShrineLight->SetVisibility(true);
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Shrine Activated"));
	}
	
}


