#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class AProjectile;

UCLASS()
class TOONTANKS_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();

	virtual void HandleDestruction();
	void SetEnabledState(bool bState);
	void RotateTurret(const FVector& LookAtTarget) const;
	void Fire();
	void ChangeProjectileClass(TSubclassOf<::AProjectile> Projectile);

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookRightRate(float AxisValue);
	
	UPROPERTY(EditAnywhere)
	int ProjectilesPerShot = 1;

protected:
	virtual void Tick(float DeltaTime) override;

	UStaticMeshComponent* GetTurretMesh() const { return TurretMesh; }

private:
	FVector GetMovementVector() const;
	void Move();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turret", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turret", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turret", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category = "Turret", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UParticleSystem* DeathParticles;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	USoundBase* DeathSound;
	
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float FireDelay = 0.5f;

	UPROPERTY(VisibleInstanceOnly, Category = "Combat")
	float NextFireTime;

	UPROPERTY(EditAnywhere)
	float RotationRate = 10;

	float BaseRotationInterpolationSpeed = 5.f;
	float TurretRotationInterpolationSpeed = 25.f;

	float AdditionalProjectileGap = 50.f;

	float MovementXValue = 0;
	float MovementYValue = 0;
	
	UPROPERTY(EditAnywhere)
	bool bIsEnabled;
};
