// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

APlayerCharacter::APlayerCharacter()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArmComponent->SetupAttachment(GetTurretMesh());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	HatMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hat Mesh"));
	HatMesh->SetupAttachment(GetTurretMesh());
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	TankPlayerController = Cast<APlayerController>(GetController());
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	HandleFiring();
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction<FTriggerFireDelegate>(TEXT("Fire"), IE_Pressed, this, &APlayerCharacter::TriggerFire, true);
	PlayerInputComponent->BindAction<FTriggerFireDelegate>(TEXT("Fire"), IE_Released, this, &APlayerCharacter::TriggerFire, false);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ABaseCharacter::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &ABaseCharacter::LookRightRate);
}

void APlayerCharacter::HandleFiring()
{
	if (bCanFire)
	{
		Fire();
	}
}

void APlayerCharacter::HandleDestruction()
{
	Super::HandleDestruction();
	    
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);

	CameraComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
}

void APlayerCharacter::TriggerFire(bool bState)
{
	bCanFire = bState;
}

void APlayerCharacter::SetHatMesh(UStaticMesh* StaticMesh)
{
	if (HatMesh == nullptr)
	{
		return;
	}
	
	HatMesh->SetStaticMesh(StaticMesh);
}
