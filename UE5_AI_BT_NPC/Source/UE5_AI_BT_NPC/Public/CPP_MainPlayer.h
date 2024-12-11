// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPP_MainPlayer.generated.h"

class CPP_BehaviourTree;

UCLASS(Blueprintable)
class UE5_AI_BT_NPC_API ACPP_MainPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACPP_MainPlayer();

	UFUNCTION(BlueprintCallable)
		void MovRight(float inputValue);
	UFUNCTION(BlueprintCallable)
    	void MovForward(float inputValue);
	UFUNCTION(BlueprintCallable)
		void Turn(float inputValue);
	UFUNCTION(BlueprintCallable)
		void LookUp(float inputValue);
	UFUNCTION(BlueprintCallable)
		void WriteDataToFile(const FString& Content);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	float m_Speed;
};
