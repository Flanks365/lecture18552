// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Core/Lecture8552_PlayerController.h"
#include "Engine/Engine.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interactable/Crate.h"
#include "Interactable/Safe.h"
#include "TimerManager.h"
#include "Interactable/Shrine.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnchancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Default Actions
		EnchancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		
		//move
		EnchancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		
		//jump
		EnchancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &APlayerCharacter::onJumpStart);
		EnchancedInputComponent->BindAction(JumpAction, ETriggerEvent::Ongoing, this, &APlayerCharacter::onJumpOngoing);
		EnchancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APlayerCharacter::onJumpComplete);
		EnchancedInputComponent->BindAction(JumpAction, ETriggerEvent::Canceled, this, &APlayerCharacter::onJumpCanceled);
		
		EnchancedInputComponent->BindAction(FlyAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Fly);
		EnchancedInputComponent->BindAction(LandAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Land);
		
		//interact
		EnchancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &APlayerCharacter::Interact);
		
	}
}

void APlayerCharacter::RestoreEnergy(float Amount)
{
	
	// if (GEngine)
	// {
	// 	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Restoring Energy: %f"), Amount));
	// }
	Energy = FMath::Clamp(Energy + Amount, 0.0f, MaxEnergy);
	
	OnEnergyChanged.Broadcast(Energy, MaxEnergy);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	if (!GetController()) return;
	
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	
	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
	
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	if (!GetController()) return;
	
	FVector2D MoveAxisVector = Value.Get<FVector2D>();
	
	AddMovementInput(GetActorForwardVector(), MoveAxisVector.X);
	AddMovementInput(GetActorRightVector(), MoveAxisVector.Y);
	
}

void APlayerCharacter::Interact(const FInputActionValue& Value)
{
	FVector StartLocation;
	FRotator ViewRotation;
	
	GetActorEyesViewPoint(StartLocation, ViewRotation);
	
	FVector ForwardVector = ViewRotation.Vector();
	
	FVector Endlocation = StartLocation + (ForwardVector * 200);
	
	FHitResult HitResult;
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);
	
	// bool bHit = GetWorld()->LineTraceSingleByChannel(
	// 	HitResult,StartLocation,Endlocation,ECC_Visibility,TraceParams);
	//
	// FColor LineColor = bHit ? FColor::Green : FColor::Red;
	//
	// DrawDebugLine(GetWorld(), StartLocation, Endlocation, LineColor, false, 2.0f, 0, 1.5f);
	
	FCollisionShape Sphere = FCollisionShape::MakeSphere(130.0f);
	
	bool bHit = GetWorld()->SweepSingleByChannel(
		HitResult, StartLocation, Endlocation, FQuat::Identity, ECC_Visibility, Sphere, TraceParams);
	
	DrawDebugSphere(GetWorld(), HitResult.Location, 130.0f, 12, FColor::Yellow,false,2.0f);
	
	if (!bHit)
	{
		return;
	}
	
	AActor* HitActor = HitResult.GetActor();
	UPrimitiveComponent* HitComponent = HitResult.GetComponent();
	
	if (!HitActor) return;
	
	if (IInteractable* Interactable = Cast<IInteractable>(HitActor))
	{
		Interactable->Interact(HitComponent);
	}
	
	// if (AShrine* Shrine = Cast<AShrine>(HitActor))
	// {
	// 	Shrine->Activate();
	// } else if (ACrate* Crate = Cast<ACrate>(HitActor))
	// {
	// 	Crate->open();
	// } else if (ASafe* Safe = Cast<ASafe>(HitActor))
	// {
	// 	if (HitComponent == Safe->LootMesh)
	// 	{
	// 		Safe->CollectLoot();
	// 	} else
	// 	{
	// 		Safe->Open();
	// 	}
	// }
	
	

}


void APlayerCharacter::onJumpStart(const FInputActionValue& Value)
{
	if (!CanJump()) return;
	
	
	Jump();
}

void APlayerCharacter::onJumpOngoing(const FInputActionValue& Value)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Green, TEXT("Powering up...."));
	}
}

void APlayerCharacter::onJumpCanceled(const FInputActionValue& Value)
{
	StopJumping();
}

void APlayerCharacter::onJumpComplete(const FInputActionValue& Value)
{
	if (!GetCharacterMovement()->IsFalling())
	{
		return;
	}
	
	if (Energy > 0.0f)
	{
		GetCharacterMovement()->SetMovementMode(MOVE_Flying);
	}
	
	if (ALecture8552_PlayerController* pc = Cast<ALecture8552_PlayerController>(GetController()))
	{
		if (Energy > 0.0f)
		{
			pc->addInputFlyingContext();
			
			
			
			GetWorldTimerManager().SetTimer(PlayerTimerHandle,[this,Value](){
				
			RestoreEnergy(-1.0f);
				
			if (Energy <= 0.0f)
			{
				Land(Value);
			}
				
		}, 0.2f, true);
		}
	}
}

void APlayerCharacter::Fly(const FInputActionValue& Value)
{
	if (!GetController()) return;
	
	float FlyValue = Value.Get<float>();
	
	AddMovementInput(GetActorUpVector(), FlyValue);
	
	if (Energy <= 0.0f)
	{
		Land(Value);
	} else
	{
		Energy = FMath::Clamp<float>(Energy - 1.0f, 0.0f, MaxEnergy);
		OnEnergyChanged.Broadcast(Energy, MaxEnergy);
	}
}

void APlayerCharacter::Land(const FInputActionValue& Value)
{
	if (!GetController()) return;
	
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	
	if (ALecture8552_PlayerController* pc = Cast<ALecture8552_PlayerController>(GetController()))
	{
		pc->removeInputFlyingContext();
	}
	
	GetWorldTimerManager().ClearTimer(PlayerTimerHandle);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


