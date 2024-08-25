// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Animation/AnimMontage.h" 

#include "MyEnemy.generated.h"

UENUM(BlueprintType)
enum class EEnemyActionState : uint8
{
	EAS_Onoccupied UMETA(Displayname = "Unoccupied"),
	EAS_Attacking UMETA(Displayname = "Attacking")
};

UCLASS()
class FIRSTGAME_API AMyEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle TimerHandle, DestroyHandler;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetHealth(float value);

	float GetHealth() {
		return Health;
	}

private:
	void HandleDeath();
	void DestroyEnemy();
	void OnAttackEnd();
	void PlayAttackMontage();
	UFUNCTION(BlueprintCallable, Category = "MyEnemy")
	void Attack();

private:
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float Health = 20.0f;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool EnemyAlive = true;

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* AttackMontage;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EEnemyActionState ActionState = EEnemyActionState::EAS_Onoccupied;
};
