// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class TOONTANKS_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	APlayerCharacter();
	
	virtual void Tick(float DeltaTime) override;
	virtual void HandleDestruction() override;
	
	APlayerController* GetTankPlayerController() const { return TankPlayerController; }
	void SetHatMesh(UStaticMesh* Hat);
	
protected:
	virtual void BeginPlay() override;

private:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	void TriggerFire(bool bState);
	void HandleFiring();
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hat", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* HatMesh;

	DECLARE_DELEGATE_OneParam(FTriggerFireDelegate, const bool);

	bool bIsEnabled = false;
	bool bCanFire;
	
	APlayerController* TankPlayerController;
};
