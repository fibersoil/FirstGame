// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    //PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
    //RootComponent = PlayerMesh;
    PlayerSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("PlayerSpringArm"));
    PlayerSpringArm->SetupAttachment(RootComponent);
    //PlayerSpringArm->SetupAttachment(PlayerMesh);
    PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
    PlayerCamera->SetupAttachment(PlayerSpringArm);
}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Register axis
    PlayerInputComponent->BindAxis(TEXT("MoveFB"), this, &AMyPlayer::MoveFB);
    PlayerInputComponent->BindAxis(TEXT("MoveLR"), this, &AMyPlayer::MoveLR);
    PlayerInputComponent->BindAxis(TEXT("Rotate"), this, &AMyPlayer::Rotate);
}

void AMyPlayer::MoveFB(float Value)
{
    AddMovementInput(PlayerCamera->GetForwardVector(), Value * MoveSpeed);
}

void AMyPlayer::MoveLR(float Value)
{
    AddMovementInput(-PlayerCamera->GetRightVector(), Value * MoveSpeed);
}

void AMyPlayer::Rotate(float Value)
{
    AddControllerYawInput(Value * RotationSpeed);
}
