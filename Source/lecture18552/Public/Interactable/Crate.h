// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "Crate.generated.h"

class UItemDataAsset;

UCLASS()
class LECTURE18552_API ACrate : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACrate();
	
	virtual void Interact(AActor* Interactor, UPrimitiveComponent* HitComponent) override;
	void open();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> BaseMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> Lid;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "item")
	TObjectPtr<UItemDataAsset> Potion;
	
};
