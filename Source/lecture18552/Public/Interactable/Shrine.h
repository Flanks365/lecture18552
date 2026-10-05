// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "Shrine.generated.h"

class UPointLightComponent;

UCLASS()
class LECTURE18552_API AShrine : public AActor , public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AShrine();
	
	virtual void Interact(UPrimitiveComponent* HitComponent) override;
	
	void Activate();
	
	bool bIsActive = false;
	
protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> BaseMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UPointLightComponent> ShrineLight;


};
