// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/DarioBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Engine/StaticMesh.h"
#include "DarioAnimInstance.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "PortalComputer.h"
#include "Dario64GameInstance.h"
// Sets default values
ADarioBase::ADarioBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComp->SetupAttachment(RootComponent);

	BaseLookRightRate = 45.0f;
	BaseLookUpRate = 45.0f;
	Sprint = 2.0f;
	HighJumping = 2.0f;
	LongJumping = 5.0f;

	SetupStimulus();

	//Animr = (UDarioAnimInstance*)GetMesh()->GetAnimInstance();
}

void ADarioBase::EnableGun_Implementation()
{
	MeshComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "LeftHandSocket");
	MeshComp->SetVisibility(true);
	hasGun = true;
}

void ADarioBase::DisableGun_Implementation()
{
	//Just in case
	MeshComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "LeftHandSocket");
	MeshComp->SetVisibility(false);
	hasGun = false;
}

void ADarioBase::SetTargetComputer(APortalComputer* _target)
{
	targetPortal = _target;
}

void ADarioBase::ClearTargetComputer()
{
	targetPortal = nullptr;
}

void ADarioBase::Interact()
{
	if (targetPortal != nullptr)
	{
		//GetMesh()->SetMaterial(0, targetPortal->dissolveMat);
		
		//SetActorLocation(targetPortal->DarioPosition);

		DisableInput(GetWorld()->GetFirstPlayerController());

		targetPortal->Transition(this);

	}
}

void ADarioBase::MoveForward(float Value)
{
	if ((Controller) && (Value != 0))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);

		//GetMesh()->GetAnimInstance().
	}
}

void ADarioBase::MoveRight(float Value)
{
	if ((Controller) && (Value != 0))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void ADarioBase::Jump()
{
	Super::Jump();

	//Animr->AnimState = 1;
	((UDarioAnimInstance*)GetMesh()->GetAnimInstance())->AnimState = 1;
}

void ADarioBase::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	((UDarioAnimInstance*)GetMesh()->GetAnimInstance())->AnimState = 0;
}

void ADarioBase::Sprinting()
{
	GetCharacterMovement()->MaxWalkSpeed *= Sprint;
}

void ADarioBase::StopSprinting()
{
	GetCharacterMovement()->MaxWalkSpeed /= Sprint;
}

void ADarioBase::HighJump()
{
	GetCharacterMovement()->JumpZVelocity *= HighJumping;
}

void ADarioBase::StopHighJump()
{
	GetCharacterMovement()->JumpZVelocity /= HighJumping;
}

void ADarioBase::LongJump()
{
	GetCharacterMovement()->Velocity *= LongJumping;
}

void ADarioBase::StopLongJump()
{
	GetCharacterMovement()->Velocity /= LongJumping;
}

void ADarioBase::LookRightRate(float Value)
{
	AddControllerYawInput(Value * BaseLookRightRate * GetWorld()->GetDeltaSeconds());
}

void ADarioBase::LookUpRate(float Value)
{
	AddControllerPitchInput(Value * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ADarioBase::SpawnProjectile()
{
	if (Ammo > 0 && hasGun)
	{
		Ammo -= 1;
		BulletsFired += 1;
		UDario64GameInstance* instanceRef = Cast<UDario64GameInstance>(GetGameInstance());
		instanceRef->totalBulletsFired += 1;
		if (Shoot) {
			PlayAnimMontage(Shoot);
		}
		const FVector Location = GetMesh()->GetSocketLocation("LeftHandSocket") + FVector(0.0f, 0.0f, 20.0f);  //  GetActorLocation();


		const FRotator Rotation = GetActorRotation();

		GetWorld()->SpawnActor<AActor>(Projectile, Location, Rotation);
	}
}


void ADarioBase::MeleeAttack()
{
	if (hasGun) 
	{
		if (Melee) {
			PlayAnimMontage(Melee);
		}
	}
}

// Called to bind functionality to input
void ADarioBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ADarioBase::Sprinting);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ADarioBase::StopSprinting);

	PlayerInputComponent->BindAction("HighJump", IE_Pressed, this, &ADarioBase::HighJump);
	PlayerInputComponent->BindAction("HighJump", IE_Released, this, &ADarioBase::StopHighJump);

	PlayerInputComponent->BindAction("LongJump", IE_Pressed, this, &ADarioBase::LongJump);
	PlayerInputComponent->BindAction("LongJump", IE_Released, this, &ADarioBase::StopLongJump);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ADarioBase::Interact);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ADarioBase::SpawnProjectile);
	//PlayerInputComponent->BindAction("Shoot", IE_Released, this, &ADarioBase::StopLongJump);

	PlayerInputComponent->BindAction("Melee", IE_Pressed, this, &ADarioBase::MeleeAttack);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADarioBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADarioBase::MoveRight);

	PlayerInputComponent->BindAxis("LookRightRate", this, &ADarioBase::LookRightRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ADarioBase::LookUpRate);
}

void ADarioBase::BeginPlay()
{
	Super::BeginPlay();
	OnControllerConnectionHandle = FCoreDelegates::OnControllerConnectionChange.AddUFunction(this, FName("OnControllerConnectionChange"));

	//EnableGun();
}

void ADarioBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	FCoreDelegates::OnControllerConnectionChange.Remove(OnControllerConnectionHandle);

	
}

void ADarioBase::OnControllerConnectionChange_Implementation(bool Connected, int32 UserID, int32 ControllerID)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Connection change, Controller ID: %d, Connected: %d"), ControllerID, Connected));
}

// ------------------ AI related function ------------------ //

void ADarioBase::SetupStimulus()
{
	stimulus = CreateDefaultSubobject <UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));
	stimulus->RegisterForSense(TSubclassOf<UAISense_Sight>());
	stimulus->RegisterWithPerceptionSystem();
}