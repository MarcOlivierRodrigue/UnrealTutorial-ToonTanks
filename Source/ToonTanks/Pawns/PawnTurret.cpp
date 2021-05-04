// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "Pawns/PawnTank.h"


// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
    Super::BeginPlay();

    GetWorld() -> GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

    PlayerPawn = Cast<APawnTank> (UGameplayStatics::GetPlayerPawn(this, 0));
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APawnTurret::CheckFireCondition()
{
    if (!PlayerPawn) 
    {
        return;
    }

    if (GetDistanceToPlayer() <= FireRange)
    {
        UE_LOG(LogTemp, Warning, TEXT("FIRE!!!"));
    }

    UE_LOG(LogTemp, Warning, TEXT("CheckFireCondition triggered"));
}

float APawnTurret::GetDistanceToPlayer()
{
    if (!PlayerPawn) 
    {
        return 0.f;
    }

    return FVector::Dist(PlayerPawn -> GetActorLocation(), GetActorLocation());
}