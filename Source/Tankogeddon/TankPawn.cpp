// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "TankController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/ArrowComponent.h"
#include "Cannon.h"



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

void ATankPawn::RotateRight(float Value)
{
	TargetRotateAxisValue = Value;
}


void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	Controller = Cast<ATankController>(GetController());

	SetupCannon();
}

void ATankPawn::SetupCannon()
{
	if (Cannon)
	{
		Cannon->Destroy();
	}
	FActorSpawnParameters spawnParams;
	spawnParams.Instigator = this;
	spawnParams.Owner = this;

	Cannon = GetWorld()->SpawnActor<ACannon>(CannonClass, spawnParams);
	Cannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

}

void ATankPawn::Fire()
{
	Cannon->Fire();
}

void ATankPawn::FireSpecial()
{
	Cannon->FireSpecial();
}

void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector ActorLocation = GetActorLocation();
	FVector ForvardVector = GetActorForwardVector();
	FVector movePosition = ActorLocation + ForvardVector * MoveSpeed * TargetForwardAxisValue * DeltaTime;
	SetActorLocation(movePosition, true);

	float CurrentRotateAxisValue = FMath::Lerp(CurrentRotateAxisValue, TargetRotateAxisValue, RotateInterpolationKey);
	float YawRotation = CurrentRotateAxisValue * RotationSpeed * DeltaTime;
	FRotator ActionRotation = GetActorRotation();
	YawRotation = ActionRotation.Yaw + YawRotation;
	FRotator NewRotation = FRotator(0, YawRotation, 0);
	SetActorRotation(NewRotation);

	if (Controller)
	{
		FVector mousePosition = Controller -> GetMousePosition();
		FRotator currRotation = TurretMesh->GetComponentRotation();
		FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), mousePosition);
		targetRotation.Pitch = currRotation.Pitch;
		targetRotation.Roll = currRotation.Roll;

		TurretMesh->SetWorldRotation(FMath::Lerp (currRotation, targetRotation, TurretRotateInterpolationKey));
	}	
}

