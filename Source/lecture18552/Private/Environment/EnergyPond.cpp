// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/EnergyPond.h"
#include "TimerManager.h"

#include "Character/PlayerCharacter.h"


// Sets default values
AEnergyPond::AEnergyPond()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}



void AEnergyPond::OnOverlapBegin_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin_Implementation(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep,
										 SweepResult);
	
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor))
	{
		// Start regenerating energy
		
		TWeakObjectPtr<APlayerCharacter> WeakCharacter = Cast<APlayerCharacter>(Player);
		
		GetWorldTimerManager().SetTimer(EnergyPondTimerHandle,[WeakCharacter,this](){
			
			if (WeakCharacter.IsValid())
			{
				//restore energy
				WeakCharacter->RestoreEnergy(EnergyRegenRate);
				
			}
		}, RegenInterval, true);
		
			
	}
}

void AEnergyPond::OnOverlapEnd_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd_Implementation(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	
	if (Cast<APlayerCharacter>(OtherActor))
	{
		GetWorldTimerManager().ClearTimer(EnergyPondTimerHandle);
	}
}