#include "CPP_NPC.h"
#include "CPP_LeafWalk.h"
#include "CPP_LeafDriveLeft.h"
#include "CPP_LeafDriveRight.h"
#include "CPP_SequenceNode.h"
#include "CPP_SelectorNode.h"
#include "CPP_BehaviourTree.h"
#include "CPP_EvaluateNPC.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
bool isTrue()
{
	return true;
}

bool isFalse(bool value)
{
	return value;
}

bool isSeeingRoad(TWeakObjectPtr<UMaterialInterface> mat)
{
	if (!mat.IsValid())
		return false;
	if (mat.IsValid())
	{
		//UE_LOG(LogTemp, Warning, TEXT("Mat: %s"), *mat->GetName());
	}
	if(mat->GetName() == "road" || mat->GetName() == "MAT_Allowed")
		return true;
	return false;
}

bool isSeeingRoadBoth(TWeakObjectPtr<UMaterialInterface> mat, TWeakObjectPtr<UMaterialInterface> mat2)
{
	return isSeeingRoad(mat) && isSeeingRoad(mat2);
}

ACPP_NPC::ACPP_NPC()
{
	PrimaryActorTick.bCanEverTick = true;

	SetCurrentLookAtMaterial();
	
	CPP_SequenceNode* sequenceNode = new CPP_SequenceNode(this);
	CPP_SelectorNode* selectNode = new CPP_SelectorNode(this);
	CPP_LeafWalk* walkLeaf = new CPP_LeafWalk(this);
	CPP_LeafDriveLeft* driveLeftLeaf = new CPP_LeafDriveLeft(this);
	CPP_LeafDriveRight* driveRightLeaf = new CPP_LeafDriveRight(this);
	selectNode->AddChild(walkLeaf,
		[this](){
			return isSeeingRoadBoth(m_CurrentLeftMaterial, m_CurrentRightMaterial);
		});
	selectNode->AddChild(driveLeftLeaf,
	[this](){
		return !isSeeingRoad(m_CurrentRightMaterial);
	});
	selectNode->AddChild(driveRightLeaf,
	[this](){
		return !isSeeingRoad(m_CurrentLeftMaterial);
	});
	//selectNode->AddChild(leafNode2, isTrue);
	//selectNode->AddChild(leafNode3, isFalse);
	m_BehaviourTree = new CPP_BehaviourTree{selectNode};

	m_EvaluateNPC = new CPP_EvaluateNPC{};
}

ACPP_NPC::~ACPP_NPC()
{
}

void ACPP_NPC::BeginPlay()
{
	Super::BeginPlay();

	if (GetCharacterMovement())
	{
		UE_LOG(LogTemp, Warning, TEXT("MaxWalkSpeed set to: %f"), GetCharacterMovement()->MaxWalkSpeed);
		GetCharacterMovement()->MaxWalkSpeed = 3000.f;
	}
}

void ACPP_NPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(m_Driving)
	{
		SetCurrentLookAtMaterial();
		m_BehaviourTree->ExecuteTree();
		m_EvaluateNPC->AddTrackTimer(DeltaTime);
	}
}

void ACPP_NPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACPP_NPC::StartDriving()
{
	m_Driving = !m_Driving;
}

UMaterialInterface* ACPP_NPC::GetMaterial(FVector start, FVector end)
{
	FHitResult HitResult{};

	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);
	
	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,     
		start,         
		end,           
		ECC_Visibility,
		TraceParams    
	);

	FColor LineColor = bHit ? FColor::Green : FColor::Red;
	DrawDebugLine(
		GetWorld(),
		start,
		end,
		LineColor,
		false, 
		2.0f,  
		0,     
		2.0f   
	);

	UMaterialInterface* HitMaterial{};
	if (bHit)
	{
		UPrimitiveComponent* HitComponent = HitResult.Component.Get();

		if (HitComponent)
		{
			HitMaterial = HitComponent->GetMaterial(0);
			if (HitMaterial)
			{
				//UE_LOG(LogTemp, Warning, TEXT("Hit Material: %s"), *HitMaterial->GetName());
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

	return HitMaterial;
}

void ACPP_NPC::SetCurrentLookAtMaterial()
{
	float rayLength = 500.f;
	
	FVector Start = GetActorLocation();
	FVector ForwardVector = GetActorForwardVector();
	FVector RightVector = GetActorRightVector();
	FVector DownwardVector = FVector(0.0f, 0.0f, -1.0f);
	FVector LeftDownwardVector = (RightVector * -1.0f + DownwardVector * 0.7f).GetSafeNormal();
	m_EndLeftRay = Start + ForwardVector * rayLength + LeftDownwardVector * rayLength;
	FVector RightDownwardVector = (RightVector * 1.0f + DownwardVector * 0.7f).GetSafeNormal();
	m_EndRightRay = Start + ForwardVector * rayLength + RightDownwardVector * rayLength;

	m_CurrentLeftMaterial = MakeWeakObjectPtr(GetMaterial(Start, m_EndLeftRay));
	m_CurrentRightMaterial = MakeWeakObjectPtr(GetMaterial(Start, m_EndRightRay));
}
