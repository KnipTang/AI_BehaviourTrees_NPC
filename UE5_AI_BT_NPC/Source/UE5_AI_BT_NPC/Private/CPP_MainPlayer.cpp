// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_MainPlayer.h"

// Sets default values
ACPP_MainPlayer::ACPP_MainPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_MainPlayer::BeginPlay()
{
	Super::BeginPlay();

	a.emplace_back(1);
}

// Called every frame
void ACPP_MainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACPP_MainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}

void ACPP_MainPlayer::SpawnActor()
{
	a.at(0)++;
	
	FActorSpawnParameters spawnParameters;
	spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	GetWorld()->SpawnActor<AActor>(actorBPToSpawn, GetActorTransform(), spawnParameters);
}
