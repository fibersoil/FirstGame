// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemy.h"

// Sets default values
AMyEnemy::AMyEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyEnemy::SetHealth(float value)
{
	Health = value;
	if (Health <= 0.0f) {
		EnemyAlive = false;
		HandleDeath();
	}
}

void AMyEnemy::HandleDeath()
{
	// Enable physics simulation on the skeletal mesh to create ragdoll effect
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	GetWorldTimerManager().SetTimer(DestroyHandler, this, &AMyEnemy::DestroyEnemy, 4.0f, false);
}

void AMyEnemy::DestroyEnemy() {
	Destroy();
}

void AMyEnemy::PlayAttackMontage()
{
    UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
    if (AnimInstance && AttackMontage) {
        AnimInstance->Montage_Play(AttackMontage);
    }
}

void AMyEnemy::Attack()
{
    const bool CanAttack = ActionState == EEnemyActionState::EAS_Onoccupied;
    if (CanAttack) {
        GetWorldTimerManager().SetTimer(TimerHandle, this, &AMyEnemy::OnAttackEnd, 0.5f, false);
        PlayAttackMontage();
        ActionState = EEnemyActionState::EAS_Attacking;
    }

}

void AMyEnemy::OnAttackEnd()
{
    ActionState = EEnemyActionState::EAS_Onoccupied;
}