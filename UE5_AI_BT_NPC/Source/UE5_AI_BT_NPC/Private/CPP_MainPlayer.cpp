// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_MainPlayer.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values
ACPP_MainPlayer::ACPP_MainPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Speed = 100;
	
	GetMaterialUnder();
}

void ACPP_MainPlayer::GetMaterialUnder()
{
	FHitResult HitResult{};
	FVector Start = GetActorLocation();
	FVector ForwardVector = GetActorForwardVector();
	FVector RightVector = GetActorRightVector();
	FVector DownwardVector = FVector(0.0f, 0.0f, -1.0f);
	FVector LeftDownwardVector = (RightVector * -1.0f + DownwardVector * 0.7f).GetSafeNormal();
	FVector End = Start + ForwardVector * 200.0f + LeftDownwardVector * 200.0f;

	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);
	
	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,     
		Start,         
		End,           
		ECC_Visibility,
		TraceParams    
	);

	FColor LineColor = bHit ? FColor::Green : FColor::Red;
	DrawDebugLine(
		GetWorld(),
		Start,
		End,
		LineColor,
		false, 
		2.0f,  
		0,     
		2.0f   
	);
	
	if (bHit)
	{
		UPrimitiveComponent* HitComponent = HitResult.Component.Get();

		if (HitComponent)
		{
				UMaterialInterface* HitMaterial = HitComponent->GetMaterial(0);
				if (HitMaterial)
				{
					UE_LOG(LogTemp, Warning, TEXT("Hit Material: %s"), *HitMaterial->GetName());
				}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No component found on hit."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No hit detected."));
	}
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
	GetMaterialUnder();
}

// Called to bind functionality to input
void ACPP_MainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACPP_MainPlayer::MovRight(float inputValue)
{
	FVector rightDir = GetActorRightVector();
	AddMovementInput(rightDir, inputValue * m_Speed);
}

void ACPP_MainPlayer::MovForward(float inputValue)
{
	FVector forwardDir = GetActorForwardVector();
	AddMovementInput(forwardDir, inputValue * m_Speed);
}

void ACPP_MainPlayer::Turn(float inputValue)
{
	AddControllerYawInput(inputValue);
}

void ACPP_MainPlayer::LookUp(float inputValue)
{
	AddControllerPitchInput(inputValue);
}
