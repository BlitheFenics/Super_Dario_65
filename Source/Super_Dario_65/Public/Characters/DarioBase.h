// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DarioBase.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UStaticMeshComponent;
class USkeletalMeshComponent;
class UDarioAnimInstance;
class UAIPerceptionStimuliSourceComponent;
class APortalComputer;

UCLASS()
class SUPER_DARIO_65_API ADarioBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADarioBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		UStaticMeshComponent* MeshComp;

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	FDelegateHandle OnControllerConnectionHandle;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Input")
		void OnControllerConnectionChange(bool Connected, int32 UserID, int32 ControllerID);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
		UAnimMontage* Shoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
		UAnimMontage* Melee;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		APortalComputer* targetPortal;

	// -------------- Pickups and Variables -------------- //
	UPROPERTY(BlueprintReadWrite, Category = "Variables")
		int32 Health = 5;

	UPROPERTY(BlueprintReadWrite, Category = "Variables")
		int32 Ammo = 10;

	UPROPERTY(BlueprintReadWrite, Category = "Variables")
		int32 Rods;

	UPROPERTY(BlueprintReadWrite, Category = "Variables")
		int32 BulletsFired;

	UPROPERTY(BlueprintReadWrite, Category = "Variables")
		int32 MugshotCollected;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "DarioThings")
		void EnableGun();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "DarioThings")
		void DisableGun();

private:

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AActor> Projectile;

	// ------------- AI RELATED ------------- //
	UAIPerceptionStimuliSourceComponent* stimulus;

	void SetupStimulus();
	
	/*UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		UDarioAnimInstance* Animr;*/

protected:

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Sprinting();
	void StopSprinting();
	void HighJump();
	void StopHighJump();
	void LongJump();
	void MeleeAttack();
	void StopLongJump();
	void LookRightRate(float Value);
	void LookUpRate(float Value);

	virtual void Jump() override;
	virtual void Landed(const FHitResult& Hit);



	UFUNCTION()
	void SpawnProjectile();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
		bool hasGun;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
		float BaseLookRightRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
		float BaseLookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float Sprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float HighJumping;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
		float LongJumping;
public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
		void SetTargetComputer(APortalComputer* _target);
	
	UFUNCTION(BlueprintCallable)
		void ClearTargetComputer();

	UFUNCTION(BlueprintCallable)
		void Interact();
};