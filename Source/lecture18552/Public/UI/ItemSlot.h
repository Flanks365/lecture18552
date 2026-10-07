// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemSlot.generated.h"

class UTextBlock;
class UImage;
class UItemDataAsset;
/**
 * 
 */
UCLASS()
class LECTURE18552_API UItemSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Slot")
	TObjectPtr<UItemDataAsset> Item;
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetupSlot(UItemDataAsset* InItemDataAsset, int32 Quantity);
	
	
protected:
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Thumbnail;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> QuantityText;
};
