// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"



// Sets default values
ATankPawn::ATankPawn()
{
	// Set this pawn to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	
	PrimaryActorTick.bCanEverTick = true;
	
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank body"));
	RootComponent = BodyMesh;
	
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank turret"));
	TurretMesh->SetupAttachment(BodyMesh);
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm"));
	SpringArm->SetupAttachment(BodyMesh);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ATankPawn::MoveForvard(float Value)
{
	TargetForwardAxisValue = Value;
}

void ATankPawn::MoveRightVector(float Value)
{
	TargetRightAxisValue = Value;
}

void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector ActorLocation = GetActorLocation();
	FVector ForvardVector = GetActorForwardVector();
	FVector movePosition = ActorLocation + ForvardVector * MoveSpeed * TargetForwardAxisValue * DeltaTime;
	SetActorLocation(movePosition, true);

	FVector ActorRightVector = GetActorRightVector();
	FVector movePosition = ActorLocation + ActorRightVector * RotationSpeed * TargetRightAxisValue * DeltaTime;
	SetActorLocation(movePosition, true);
}
