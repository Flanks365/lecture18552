// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/OverlapZone.h"

#include "Components/BoxComponent.h"
#include "Engine/Engine.h"


// Sets default values
AOverlapZone::AOverlapZone()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	OverlapComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComponent"));
	RootComponent = OverlapComponent;
}



// Called when the game starts or when spawned
void AOverlapZone::BeginPlay()
{
	Super::BeginPlay();
	
	OverlapComponent->OnComponentBeginOverlap.AddDynamic(this, &AOverlapZone::OnOverlapBegin);
	OverlapComponent->OnComponentEndOverlap.AddDynamic(this, &AOverlapZone::OnOverlapEnd);
	
}


void AOverlapZone::OnOverlapBegin_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// overridden in child classes
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin"));
	}
}

void AOverlapZone::OnOverlapEnd_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// overridden in child classes
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Overlap End"));
	}
}




