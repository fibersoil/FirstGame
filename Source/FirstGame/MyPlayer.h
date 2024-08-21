// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Engine/StaticMesh.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Animation/AnimMontage.h"  

#include "MyPlayer.generated.h"

UENUM(BlueprintType)
enum class EActionState : uint8
{
	EAS_Onoccupied UMETA(Displayname = "Unoccupied"),
	EAS_Attacking UMETA(Displayname = "Attacking")
};

UCLASS()
class FIRSTGAME_API AMyPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle TimerHandle;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveFB(float Value);
	void MoveLR(float Value);
	void Rotate(float Value);

	void PlayAttackMontage();
	void Attack();
	void OnAttackEnd();

private:
	UPROPERTY(EditDefaultsOnly, Category = Montages)
		UAnimMontage* AttackMontage;
	
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		EActionState ActionState = EActionState::EAS_Onoccupied;

	UPROPERTY(EditAnywhere)
		float MoveSpeed = 1.0f;

	UPROPERTY(EditAnywhere)
		float RotationSpeed = 1.0f;

	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* PlayerMesh;
	UPROPERTY(EditDefaultsOnly)
		USpringArmComponent* PlayerSpringArm;
	UPROPERTY(EditDefaultsOnly)
		UCameraComponent* PlayerCamera;
};
