// Fill out your copyright notice in the Description page of Project Settings.

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PawnTank.h"


APawnTank::APawnTank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm -> SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera -> SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    Rotate();
    Move();
}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent -> BindAxis("MoveForward", this, &APawnTank::CalcMoveInput);
    PlayerInputComponent -> BindAxis("Turn", this, &APawnTank::CalcRotateInput);
}

void APawnTank::CalcMoveInput(float Value)
{
    MoveDirection = FVector(Value * MoveSpeed * GetWorld() -> DeltaTimeSeconds, 0, 0);
}

void APawnTank::CalcRotateInput(float Value)
{
    float RotateAmount = Value * RotateSpeed * GetWorld() -> GetDeltaSeconds();
    FRotator Rotation = FRotator(0, RotateAmount, 0);
    RotationDirection = FQuat(Rotation);
}

void APawnTank::Move()
{
    AddActorLocalOffset(MoveDirection, true);   
}

void APawnTank::Rotate()
{
    AddActorLocalRotation(RotationDirection, true);
}