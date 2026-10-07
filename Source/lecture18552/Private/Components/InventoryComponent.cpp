// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"

#include "Data/ItemDataAsset.h"
#include "Engine/Engine.h"


// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInventoryComponent::AddItem(UItemDataAsset* Item)
{
	if (!Item)
	{
		return false;
	}
	
	if (Items.Num() >= Capacity)
	{
		UE_LOG(LogTemp, Error, TEXT("Item count exceeds capacity"));
		return false;
	}
	
	Items.Add(Item);
	UE_LOG(LogTemp, Warning, TEXT("Item added"));
	
	if (GEngine)
	{
		FString DebugMessage = FString::Printf(TEXT("Found %s"), *Item->ItemData.DisplayName.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, DebugMessage);
	}
	
	OnInventoryUpdated.Broadcast();
	
	return true;
}

bool UInventoryComponent::RemoveItem(UItemDataAsset* Item)
{
	if (!Item)
	{
		return false;
	}
	
	int32 RemoveCount = Items.RemoveSingle(Item);
	
	if (RemoveCount > 0)
	{
		OnInventoryUpdated.Broadcast();
		return true;
	}
	
	return false;
}

int32 UInventoryComponent::GetQuantity(UItemDataAsset* Item) const
{
	if (!Item)
	{
		return 0;
	}

	int32 TotalCount = 0;
	for (const UItemDataAsset* InventoryItem : Items)
	{
		if (InventoryItem == Item)
		{
			TotalCount++;
		}
	}

	return TotalCount;
}

TArray<UItemDataAsset*> UInventoryComponent::GetItems() const
{
	return Items;
}

