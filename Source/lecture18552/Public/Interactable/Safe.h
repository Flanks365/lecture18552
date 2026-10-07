// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "Safe.generated.h"

class UItemDataAsset;
UCLASS()
class LECTURE18552_API ASafe : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASafe();
	
	virtual void Interact(AActor* Interactor, UPrimitiveComponent* HitComponent) override;
	
	void Open();
	void CollectLoot();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> LootMesh;
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> BaseMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Loot")
	TObjectPtr<UItemDataAsset> LootItem;
	
};
