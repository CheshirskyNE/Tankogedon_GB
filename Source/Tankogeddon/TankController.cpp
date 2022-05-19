// Fill out your copyright notice in the Description page of Project Settings.


#include "TankController.h"
#include "TankPawn.h"

ATankController::ATankController()
{
}

void ATankController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ATankController::MoveForward);
	InputComponent->BindAxis("MoveRotation", this, &ATankController::MoveRightVector);
}

void ATankController::BeginPlay()
{
	Super::BeginPlay();

	TankPawn = Cast<ATankPawn>(GetPawn());
}

void ATankController::MoveForward(float Value)
{
	TankPawn->MoveForvard(Value);
}

void ATankController::MoveRightVector(float Value)
{
	TankPawn->MoveRightVector(Value);
}


