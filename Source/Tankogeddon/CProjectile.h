#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CProjectile.generated.h"

UCLASS()
class TANKOGEDDON_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	AProjectile();

	void Start();

	//virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire|Components")
		float MoveSpeed = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire|Components")
		float MoveRate = 0.005.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire|Components")
		float Damage = 1.0f;

	FTimerHandle MovementTimerHandle;

	UFUNCTION()
		void Move();

	UFUNCTION()
		void onMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	FVector StartPosition;

};