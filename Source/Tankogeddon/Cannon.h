// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameStructs.h"
#include "GameFramework/Actor.h"
#include "Cannon.generated.h"


UCLASS()
class TANKOGEDDON_API ACannon : public AActor
{
	GENERATED_BODY()
	
public:	
	ACannon();

	void Fire();
	void FireSpecial();
	bool IsReadyToFire();
	void Reload();

	FTimerHandle ReloadTimer;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Components")
		class UStaticMeshComponent*CannonMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Components")
		class UArrowComponent*ProjectTileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Fire | Components")
		float FireRate = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Fire | Components")
		float FireRange = 1000;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Fire | Components")
		float FireDamage = 1000;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Fire | Components")
		ECannonType CannonType = ECannonType::FireProjectile;

	bool bReadyToFire = true;
};
