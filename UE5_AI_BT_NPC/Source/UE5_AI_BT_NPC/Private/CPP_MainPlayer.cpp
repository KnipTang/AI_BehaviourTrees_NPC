// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_MainPlayer.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
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
	m_Speed = 5000;

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = m_Speed;
		UE_LOG(LogTemp, Warning, TEXT("MaxWalkSpeed set to: %f"), GetCharacterMovement()->MaxWalkSpeed);
	}
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

	AddMovementInput(forwardDir , inputValue);
}

void ACPP_MainPlayer::Turn(float inputValue)
{
	AddControllerYawInput(inputValue);
	//UE_LOG(LogTemp, Warning, TEXT("Turn Input Value: %f"), inputValue);
}

void ACPP_MainPlayer::LookUp(float inputValue)
{
	AddControllerPitchInput(inputValue);
}

void ACPP_MainPlayer::WriteDataToFile(const FString& Content)
{
	FString CurrentPath = FPaths::Combine(FPaths::ProjectDir(), TEXT("Evaluation"), TEXT("NPC_Evaluation.txt"));
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	IFileHandle* FileHandle = PlatformFile.OpenWrite(*CurrentPath, true);
	if (FileHandle)
	{
		const TCHAR* Data = *Content;
		int32 Size = FCString::Strlen(Data) * sizeof(TCHAR);
		FileHandle->Write((const uint8*)Data, Size);
		
		UE_LOG(LogTemp, Log, TEXT("Content Written To: %s"), *CurrentPath);
		
		delete FileHandle;
	}
}