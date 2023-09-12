#include "BaseCharacter.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);
	
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABaseCharacter::HandleDestruction()
{
	if (DeathParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(), GetActorRotation());
	}

	if (DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}

	if (!IsPlayerControlled())
	{
		Destroy();
	}
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsEnabled)
	{
		return;
	}

	Move();
}

void ABaseCharacter::MoveForward(float AxisValue)
{
	MovementXValue = AxisValue;
}

void ABaseCharacter::MoveRight(float AxisValue)
{
	MovementYValue = AxisValue;
}

FVector ABaseCharacter::GetMovementVector() const
{
	const FRotator YawRotation = TurretMesh->GetForwardVector().Rotation();

	const FVector DirectionX = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X) * MovementXValue;
	const FVector DirectionY = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y) * MovementYValue;

	return DirectionX + DirectionY;
}

void ABaseCharacter::Move()
{
	const FVector MovementVector = GetMovementVector();

	if (!MovementVector.IsNearlyZero())
	{
		const FRotator LookAtRotation = FRotator(0.f, MovementVector.Rotation().Yaw, 0.f);

		BaseMesh->SetWorldRotation(
			FMath::RInterpTo(
				BaseMesh->GetComponentRotation(), 
				LookAtRotation, UGameplayStatics::GetWorldDeltaSeconds(this), 
				BaseRotationInterpolationSpeed));
	
	}

	AddMovementInput(MovementVector, 1);
}

void ABaseCharacter::LookRightRate(float AxisValue)
{
	if (!bIsEnabled)
	{
		return;
	}
	
	const FRotator NewRotation = FRotator(0, AxisValue * RotationRate, 0);
	TurretMesh->AddLocalRotation(FQuat(NewRotation));
}

void ABaseCharacter::SetEnabledState(bool bState)
{
	bIsEnabled = bState;
}

void ABaseCharacter::RotateTurret(const FVector& LookAtTarget) const
{
	const FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	const FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);

	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(
			TurretMesh->GetComponentRotation(), 
			LookAtRotation, UGameplayStatics::GetWorldDeltaSeconds(this), 
			TurretRotationInterpolationSpeed));
}

void ABaseCharacter::Fire()
{
	const float CurrentTimeInSeconds = GetWorld()->GetTimeSeconds();

	if (!bIsEnabled || CurrentTimeInSeconds <= NextFireTime)
	{
		return;
	}
	
	FVector Location = ProjectileSpawnPoint->GetComponentLocation();
	const FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();

	for (int i = 0; i < ProjectilesPerShot; i++)
	{
		Location = FVector(Location.X, Location.Y, Location.Z + (AdditionalProjectileGap * i));
		
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
		Projectile->SetOwner(this);
	}

	NextFireTime = CurrentTimeInSeconds + FireDelay;
}

void ABaseCharacter::ChangeProjectileClass(TSubclassOf<AProjectile> Projectile)
{
	if (ProjectileClass == nullptr || Projectile == nullptr)
	{
		return;
	}
	
	ProjectileClass = Projectile;
}

