// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_MainPlayer.h"
#include "Engine/World.h"

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

void ACPP_MainPlayer::MovRight(float inputValue)
{
	FVector rightDir = GetActorRightVector();
	AddMovementInput(rightDir, inputValue);
}

void ACPP_MainPlayer::MovForward(float inputValue)
{
	FVector forwardDir = GetActorForwardVector();
	AddMovementInput(forwardDir, inputValue);
}

void ACPP_MainPlayer::Turn(float inputValue)
{
	AddControllerYawInput(inputValue);
}

void ACPP_MainPlayer::LookUp(float inputValue)
{
	AddControllerPitchInput(inputValue);
}
