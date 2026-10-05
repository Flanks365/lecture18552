// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OverlapZone.h"
#include "EnergyPond.generated.h"

UCLASS()
class LECTURE18552_API AEnergyPond : public AOverlapZone
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnergyPond();

	virtual void OnOverlapBegin_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
	virtual void OnOverlapEnd_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	
private:
	FTimerHandle EnergyPondTimerHandle;
	
	UPROPERTY(EditAnywhere, Category = "EnergyPond")
	float EnergyRegenRate = 5.0f;
	
	UPROPERTY(EditAnywhere, Category = "EnergyPond")
	float RegenInterval = 0.2f;
};
