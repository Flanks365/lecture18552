// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ItemSlot.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Data/ItemDataAsset.h"
#include "Engine/Texture2D.h"

void UItemSlot::SetupSlot(UItemDataAsset* InItemDataAsset, int32 Quantity)
{
	if (!InItemDataAsset)
	{
		if (Thumbnail)
		{
			Thumbnail->SetBrushFromTexture(nullptr);
		}
		if (QuantityText)
		{
			QuantityText->SetText(FText::GetEmpty());
		}
		
		return;
	}
	
	if (QuantityText)
	{
		FText QuantityTextFormatted = FText::Format(FText::FromString(TEXT("x{0} ")), FText::AsNumber(Quantity));
		QuantityText->SetText(QuantityTextFormatted);
	}
	
	if (Thumbnail)
	{
		if (InItemDataAsset->ItemData.ItemIcon.IsNull())
		{
			Thumbnail->SetBrushFromTexture(nullptr);
			return;
		}
		
		if (UTexture2D* LoadedTexture = InItemDataAsset->ItemData.ItemIcon.Get())
		{
			Thumbnail->SetBrushFromTexture(LoadedTexture);
		} else
		{
			UTexture2D* texture = InItemDataAsset->ItemData.ItemIcon.LoadSynchronous();
			Thumbnail->SetBrushFromTexture(texture);
		}
	}
}
