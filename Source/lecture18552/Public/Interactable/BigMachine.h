// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "BigMachine.generated.h"

UCLASS()
class LECTURE18552_API ABigMachine : public AActor, public IInteractable
{

	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABigMachine();
	virtual void Interact(AActor* Interactor, UPrimitiveComponent* HitComponent) override;
	void poof();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> BaseMesh;
	
};
