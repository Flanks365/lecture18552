// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Lecture8552_PlayerController.h"

#include "Engine/LocalPlayer.h"
#include "EnhancedInputSubsystems.h"



void ALecture8552_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (IsLocalController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				//walking / ground context = prio 0 (wasd)
				// look around with mouse will be prio 0
				//flying will be prio 1 (q and e) activated by holding spacebar turned off by tapping space bar
					Subsystem->AddMappingContext(CurrentContext, 0);
			}
			
		
		}
	}
}

void ALecture8552_PlayerController::addInputFlyingContext()
{
	if (!IsLocalController()) return;
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		
			Subsystem->AddMappingContext(FlyingMappingContext, 1);
		
	}
}

void ALecture8552_PlayerController::removeInputFlyingContext()
{
	
	if (!IsLocalController()) return;
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		
		Subsystem->RemoveMappingContext(FlyingMappingContext);
		
	}
}
