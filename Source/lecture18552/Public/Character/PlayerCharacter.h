// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.generated.h"


struct FInputActionValue;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEnergyChanged, float, CUrrentEnergy, float, MaxEnergy);

UCLASS()
class LECTURE18552_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(BlueprintAssignable,BlueprintCallable, Category = "Events")
	FOnEnergyChanged OnEnergyChanged;

	UFUNCTION(BlueprintCallable, Category = "PlayerCharacter")
	void RestoreEnergy(float Amount);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> FollowCamera;
	
	UPROPERTY(EditAnywhere, Category = "Input Action")
	TObjectPtr<UInputAction> LookAction;
	
	UPROPERTY(EditAnywhere, Category = "Input Action")
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditAnywhere, Category = "Input Action")
	TObjectPtr<UInputAction> JumpAction;
	
	UPROPERTY(EditAnywhere, Category = "Input Action")
	TObjectPtr<UInputAction> FlyAction;
	
	UPROPERTY(EditAnywhere, Category = "Input Action")
	TObjectPtr<UInputAction> LandAction;
	
	UPROPERTY(EditAnywhere, Category = "Input Action")
	TObjectPtr<UInputAction> InteractAction;
	
	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	
	void Interact(const FInputActionValue& Value);
	
	void onJumpStart(const FInputActionValue& Value);
	void onJumpOngoing(const FInputActionValue& Value);
	void onJumpCanceled(const FInputActionValue& Value);
	void onJumpComplete(const FInputActionValue& Value);
	
	void Fly(const FInputActionValue& Value);
	void Land(const FInputActionValue& Value);
	
	UPROPERTY(EditAnywhere, Category = "Energy")
	float MaxEnergy = 100.0f;
	
	UPROPERTY(EditAnywhere, Category = "Energy")
	float Energy = 20.0f;

public:
	
	
};
