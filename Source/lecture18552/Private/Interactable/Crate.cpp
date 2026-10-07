// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable/Crate.h"

#include "Components/InventoryComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ACrate::ACrate()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;
	
	Lid = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Lid"));
	Lid-> SetupAttachment(RootComponent);

}

void ACrate::Interact(AActor* Interactor, UPrimitiveComponent* HitComponent)
{
	if (!Interactor)
		return;
	
	UInventoryComponent* Inventory = Interactor->FindComponentByClass<UInventoryComponent>();
	
	if (!Inventory) return;
	
	Inventory->AddItem(Potion);
	open();
	
}

void ACrate::open()
{
	
	if (Lid)
	{
		Lid->Play(false);
	}
	
}



