// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHud.generated.h"

class UInventoryComponent;
class UItemSlot;
/**
 * 
 */
UCLASS()
class LECTURE18552_API UMainHud : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void RefreshQuantities();
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UItemSlot> Slot0;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UItemSlot> Slot1;
	
private:
	UPROPERTY()
	TObjectPtr<UInventoryComponent> InventoryComponent;
};
