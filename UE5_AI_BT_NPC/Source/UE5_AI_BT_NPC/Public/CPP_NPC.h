// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPP_NPC.generated.h"

class CPP_BehaviourTree;
class CPP_EvaluateNPC;
class CPP_BaseNode;

UENUM(BlueprintType)
enum class NPCType : uint8
{
	Basic2Lines UMETA(DisplayName = "Basic2Lines"),
	MiddleDriver UMETA(DisplayName = "MiddleDriver")
};
UCLASS()
class UE5_AI_BT_NPC_API ACPP_NPC : public ACharacter
{
	GENERATED_BODY()
	
	
public:
	// Sets default values for this character's properties
	ACPP_NPC();
	~ACPP_NPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterialInterface* m_RoadMaterial;
	UFUNCTION(BlueprintCallable)
	void StartDriving();
	UFUNCTION(BlueprintCallable, Category = "NPC Functions")
	void SetNPCType(NPCType npcType);

	float GetRotationAngle() {return m_RotationAngle;}
private:
	FHitResult* GetHitResult(FVector start, FVector end); 
	void SetCurrentLookAtMaterial();

	CPP_BaseNode* NPCtype_Basic2Line();
	CPP_BaseNode* NPCtype_MiddleDriver();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Rays")
	FVector m_EndLeftRay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Rays")
	FVector m_EndRightRay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Rays")
	float m_RayLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Rays")
	bool debugLines;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	bool m_Driving;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	float m_Speed = 2000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	float m_RotationAngle = 30;
private:
	CPP_BehaviourTree* m_BehaviourTree;
	TWeakObjectPtr<UMaterialInterface> m_CurrentLeftMaterial;
	TWeakObjectPtr<UMaterialInterface> m_CurrentRightMaterial;
	
	TOptional<FHitResult> m_CurrentHitResultLeft;
	TOptional<FHitResult> m_CurrentHitResultRight;
	
	CPP_EvaluateNPC* m_EvaluateNPC;

	
};
