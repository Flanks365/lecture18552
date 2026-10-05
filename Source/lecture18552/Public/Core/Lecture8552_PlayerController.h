// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Lecture8552_PlayerController.generated.h"

class UInputMappingContext;
/**
 * 
 */
UCLASS()
class LECTURE18552_API ALecture8552_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void addInputFlyingContext();
	void removeInputFlyingContext();
	
	
protected:
	UPROPERTY(EditAnywhere, Category = "Input")
	TArray<UInputMappingContext*> DefaultMappingContexts;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* FlyingMappingContext;
	
	virtual void SetupInputComponent() override;
	
	
};
