// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainHud.h"

#include "GameFramework/Pawn.h"
#include "UI/ItemSlot.h"
#include "Components/InventoryComponent.h"

void UMainHud::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (APlayerController* PC = GetOwningPlayer())
	{
		if (APawn* Pawn = PC->GetPawn())
		{
			InventoryComponent = Pawn->FindComponentByClass<UInventoryComponent>();
		}
	}
	
	if (InventoryComponent)
	{
		InventoryComponent->OnInventoryUpdated.AddDynamic(this, &UMainHud::RefreshQuantities);
		RefreshQuantities();
	}
}

void UMainHud::RefreshQuantities()
{
	if (!InventoryComponent) return;
	
	if (Slot0)
	{
		int32 Count = InventoryComponent->GetQuantity(Slot0->Item);
		Slot0->SetupSlot(Slot0->Item, Count);
	}
	
	if (Slot1)
	{
		int32 Count = InventoryComponent->GetQuantity(Slot1->Item);
		Slot1->SetupSlot(Slot1->Item, Count);
	}
}
