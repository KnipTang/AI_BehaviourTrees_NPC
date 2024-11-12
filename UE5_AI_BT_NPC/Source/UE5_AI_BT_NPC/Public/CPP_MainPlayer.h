// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "vector"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPP_MainPlayer.generated.h"

UCLASS()
class UE5_AI_BT_NPC_API ACPP_MainPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACPP_MainPlayer();

	UFUNCTION(BlueprintCallable)
		void SpawnActor();

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> actorBPToSpawn;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	std::vector<int> a;
};
