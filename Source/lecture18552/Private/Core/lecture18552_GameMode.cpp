// Fill out your copyright notice in the Description page of Project Settings.


#include "./Core/lecture18552_GameMode.h"
#include "./Character/BaseCharacter.h"

ALecture18552_GameMode::ALecture18552_GameMode()
{
	
	DefaultPawnClass = ABaseCharacter::StaticClass();
}
