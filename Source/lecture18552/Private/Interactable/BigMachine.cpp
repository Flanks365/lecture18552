// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable/BigMachine.h"
#include "Components/StaticMeshComponent.h"



// Sets default values
ABigMachine::ABigMachine()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;
}

void ABigMachine::poof()
{
	BaseMesh->SetVisibility(false);
}

void ABigMachine::Interact(AActor* Interactor, UPrimitiveComponent* HitComponent)
{
	poof();
}



// Called when the game starts or when spawned
