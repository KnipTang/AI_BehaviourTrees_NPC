#include "CPP_NPC.h"
#include "CPP_LeafWalk.h"
#include "CPP_LeafDriveLeft.h"
#include "CPP_LeafDriveRight.h"
#include "CPP_LeafScoping.h"
#include "CPP_LeafTurnAround.h"
#include "CPP_SequenceNode.h"
#include "CPP_SelectorNode.h"
#include "CPP_BehaviourTree.h"
#include "CPP_EvaluateNPC.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CPP_LeafResetFlipped.h"

bool isSeeingRoad(UMaterialInterface& mat)
{
	if (!mat.IsValidLowLevel())
		return false;
	if (mat.IsValidLowLevel())
	{
		//UE_LOG(LogTemp, Warning, TEXT("Mat: %s"), *mat->GetName());
	}
	if(mat.GetName() == "road" || mat.GetName() == "MAT_Allowed")
		return true;
	return false;
}

bool isSeeingRoadBoth(UMaterialInterface& mat, UMaterialInterface& mat2)
{
	return isSeeingRoad(mat) && isSeeingRoad(mat2);
}

int ACPP_NPC::NPC_IS_COUNT = -3;

ACPP_NPC::ACPP_NPC()
{
	PrimaryActorTick.bCanEverTick = true;

	m_BehaviourTree = new CPP_BehaviourTree{};

	m_EvaluateNPC = new CPP_EvaluateNPC{};

	NPC_ID = NPC_IS_COUNT;
	NPC_IS_COUNT++;
}

ACPP_NPC::~ACPP_NPC()
{
}

void ACPP_NPC::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = m_Speed;
	}
}

void ACPP_NPC::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	//NPC_IS_COUNT = 0;
}

void ACPP_NPC::Tick(float DeltaTime)
{
	
	if(m_Driving)
	{
		Super::Tick(DeltaTime);
		
		FVector Start = GetActorLocation();
		m_CurrentHitResultLeft = *GetHitResult(Start, m_EndLeftRay);
		m_CurrentHitResultRight = *GetHitResult(Start, m_EndRightRay);
		SetCurrentLookAtMaterial();
		m_BehaviourTree->ExecuteTree();
		m_EvaluateNPC->AddTrackTimer(DeltaTime);
		SetPercentageTrackCompleet();
	}

	if(debugLines)
	{
		FVector Start = GetActorLocation();
		m_CurrentHitResultLeft = *GetHitResult(Start, m_EndLeftRay);
		m_CurrentHitResultRight = *GetHitResult(Start, m_EndRightRay);
		SetCurrentLookAtMaterial();
	}
		
}

void ACPP_NPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACPP_NPC::StartDriving()
{
	m_Driving = !m_Driving;
	m_ScopingConfig.m_UnchangedDownRay = m_DownRayMultiplier;
}

void ACPP_NPC::SetNPCType(NPCType npcType)
{
	switch (npcType)
	{
	case NPCType::Basic2Lines:
		m_BehaviourTree->SetRootNode(NPCtype_Basic2Line());
		break;
	case NPCType::Basic2LinesSmart:
		m_BehaviourTree->SetRootNode(NPCtype_Basic2LineSmart());
		break;
	}
}

FHitResult* ACPP_NPC::GetHitResult(FVector start, FVector end)
{
	FHitResult* HitResult = new FHitResult();

	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);
	
	bool bHit = GetWorld()->LineTraceSingleByChannel(
		*HitResult,     
		start,         
		end,           
		ECC_Visibility,
		TraceParams    
	);

	if(debugLines)
	{
		FColor LineColor = bHit ? FColor::Green : FColor::Red;
		if(LineColor == FColor::Red)
			LineColor = FColor::Green;
		
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
	}

	UMaterialInterface* HitMaterial{};
	if (!bHit)
		UE_LOG(LogTemp, Warning, TEXT("No hit detected."));

	return HitResult;
}

void ACPP_NPC::SetCurrentLookAtMaterial()
{
	if (m_CurrentHitResultLeft.IsSet() && m_CurrentHitResultRight.IsSet())
	{
	    TWeakObjectPtr<UPrimitiveComponent> compLeft = m_CurrentHitResultLeft.GetValue().Component.Get();
	    TWeakObjectPtr<UPrimitiveComponent> compRight = m_CurrentHitResultRight.GetValue().Component.Get();
	    
	    if(compLeft != nullptr) m_CurrentLeftMaterial = compLeft->GetMaterial(0);
	    if(compRight != nullptr) m_CurrentRightMaterial = compRight->GetMaterial(0);
	}
}

void ACPP_NPC::SetPercentageTrackCompleet()
{
	float inputKey = m_Spline->FindInputKeyClosestToWorldLocation(GetActorLocation());
	float distance = m_Spline->GetDistanceAlongSplineAtSplineInputKey(inputKey);
	float length = m_Spline->GetSplineLength();
	m_PercentageTrackCurrent = (distance / length) * 100;

	if(m_PercentageTrackCurrent > m_RecordPercentageTrack)
		m_RecordPercentageTrack = m_PercentageTrackCurrent;
}

void ACPP_NPC::Finished(bool finish)
{
	FString content =
		FString::FromInt(NPC_ID) +
		TEXT(",") + FString::FromInt(finish) +
		TEXT(",") + FString::FromInt(m_EvaluateNPC->GetTrackTime()) +
		TEXT(",") + FString::FromInt(m_EvaluateNPC->GetHitBarrier()) +
		TEXT(",") + FString::FromInt(m_RotationAngle) +
		TEXT(",") + FString::FromInt(m_Speed) +
		TEXT(",") + FString::SanitizeFloat(m_ScopingConfig.m_UnchangedDownRay) +
		TEXT("\n");
	
	m_EvaluateNPC->WriteDataToFile(content);
}
void ACPP_NPC::ResetEvaluationFile()
{
	NPC_IS_COUNT = 0;
	m_EvaluateNPC->ResetFile();
}

FString ACPP_NPC::GetCurrentNodeName()
{
	return m_CurrentNode->m_NodeName;
}

CPP_BaseNode* ACPP_NPC::NPCtype_Basic2Line()
{
	CPP_SelectorNode* selectNode = new CPP_SelectorNode(this, "SelectMain");
	CPP_SequenceNode *sequenceNodeDriveleft = new CPP_SequenceNode(this, "SequenceLeft");
	CPP_SequenceNode *sequenceNodeDriveRight = new CPP_SequenceNode(this, "SequenceRight");
	CPP_LeafWalk* driveLeaf = new CPP_LeafWalk(this, "LeafWalk");
	CPP_LeafDriveLeft* driveLeftLeaf = new CPP_LeafDriveLeft(this, "LeafLeft");
	CPP_LeafDriveRight* driveRightLeaf = new CPP_LeafDriveRight(this, "LeafRight");
	
	sequenceNodeDriveleft->AddChild(driveLeaf);
	sequenceNodeDriveleft->AddChild(driveLeftLeaf);
	sequenceNodeDriveRight->AddChild(driveLeaf);
	sequenceNodeDriveRight->AddChild(driveRightLeaf);
	
	selectNode->AddChild(driveLeaf,
		[this](){
			if(m_Turning)
			{
				m_Turning = false;
			}

			return isSeeingRoadBoth(*m_CurrentLeftMaterial.Get(), *m_CurrentRightMaterial.Get());
		});
	selectNode->AddChild(sequenceNodeDriveleft,
	[this](){
		if(!m_Turning)
		{
			m_Turning = true;
			m_EvaluateNPC->HitBarrier();
		}
		return !isSeeingRoad(*m_CurrentRightMaterial.Get());
	});
	selectNode->AddChild(sequenceNodeDriveRight,
	[this](){
		if(!m_Turning)
		{
			m_Turning = true;
			m_EvaluateNPC->HitBarrier();
		}
		return !isSeeingRoad(*m_CurrentLeftMaterial.Get());
	});

	return selectNode;
}

CPP_BaseNode* ACPP_NPC::NPCtype_Basic2LineSmart()
{
	CPP_SelectorNode* selectNode = new CPP_SelectorNode(this, "SelectMain");
	CPP_SelectorNode* selectLeftOrRightNode = new CPP_SelectorNode(this, "SelectLeftOrRight");
	CPP_SequenceNode* sequenceNodeDriveLeft = new CPP_SequenceNode(this, "SequenceLeft");
	CPP_SequenceNode *sequenceNodeDriveRight = new CPP_SequenceNode(this, "SequenceRight");
	CPP_SequenceNode *sequenceNodeScoping = new CPP_SequenceNode(this, "SequenceScoping");
	CPP_LeafWalk* driveLeaf = new CPP_LeafWalk(this, "LeafWalk");
	CPP_LeafDriveLeft* driveLeftLeaf = new CPP_LeafDriveLeft(this, "LeafLeft");
	CPP_LeafDriveRight* driveRightLeaf = new CPP_LeafDriveRight(this, "LeafRight");
	CPP_LeafScoping* scopingLeaf = new CPP_LeafScoping(this, "LeafScoping");
	CPP_LeafTurnAround* turnAroundLeaf = new CPP_LeafTurnAround(this, "LeafTurnAround");
	CPP_LeafResetFlipped* resetFlippedLeaf = new CPP_LeafResetFlipped(this, "LeafResetFlipped");
	
	sequenceNodeDriveLeft->AddChild(driveLeaf);
	sequenceNodeDriveLeft->AddChild(driveLeftLeaf);
	sequenceNodeDriveRight->AddChild(driveLeaf);
	sequenceNodeDriveRight->AddChild(driveRightLeaf);
	
	sequenceNodeScoping->SetEndNodeFunctionallity(
		[this](){
			m_DownRayMultiplier = m_ScopingConfig.m_UnchangedDownRay;
	});
	sequenceNodeScoping->AddChild(scopingLeaf);
	sequenceNodeScoping->AddChild(sequenceNodeDriveLeft);

	selectNode->AddChild(resetFlippedLeaf,
	[this](){
		bool rsl = GetActorRotation().Roll > 90 || GetActorRotation().Roll < -90;
		UE_LOG(LogTemp, Display, TEXT("Rot: %f Result:%i"), GetActorRotation().Roll, rsl);
		return GetActorRotation().Roll > 90 || GetActorRotation().Roll < -90;
	});
	selectNode->AddChild(turnAroundLeaf,
	[this](){
		return m_PercentageTrackCurrent < m_RecordPercentageTrack - 0.1f;
	});
	selectNode->AddChild(driveLeaf,
	[this](){
		if(m_Turning)
		{
			m_Turning = false;
		}

		return isSeeingRoadBoth(*m_CurrentLeftMaterial.Get(), *m_CurrentRightMaterial.Get());
	});
	selectNode->AddChild(sequenceNodeDriveLeft,
	[this](){
		if(!m_Turning)
		{
			m_Turning = true;
			m_EvaluateNPC->HitBarrier();
		}
		bool rtn = !isSeeingRoad(*m_CurrentRightMaterial.Get()) && isSeeingRoad(*m_CurrentLeftMaterial.Get());
		return rtn;
	});
	selectNode->AddChild(sequenceNodeDriveRight,
	[this](){
		if(!m_Turning)
		{
			m_Turning = true;
			m_EvaluateNPC->HitBarrier();
		}
		bool rtn = !isSeeingRoad(*m_CurrentLeftMaterial.Get()) && isSeeingRoad(*m_CurrentRightMaterial.Get());
		return rtn;
	});
	selectNode->AddChild(sequenceNodeScoping,
	[this](){
		FVector end = GetActorLocation() +  FVector::CrossProduct(GetActorRightVector(),GetActorForwardVector()-500);
		FHitResult* hitResult = GetHitResult(GetActorLocation(),end);
		TWeakObjectPtr<UMaterialInterface> hitMat;
		if (hitResult)
		{
			TWeakObjectPtr<UPrimitiveComponent> comp = hitResult->Component;
			if(comp != nullptr)
			{
			hitMat = comp->GetMaterial(0);
		}
	}
	bool rtn = !isSeeingRoadBoth(*m_CurrentLeftMaterial.Get(), *m_CurrentRightMaterial.Get()) && !isSeeingRoad(*hitMat);
	return rtn;
	});
	
	selectLeftOrRightNode->AddChild(sequenceNodeDriveLeft,
		[this](){
			float leftRayLength = FVector::Dist(GetActorLocation(), m_CurrentHitResultLeft->Location);
			float rightRayLength = FVector::Dist(GetActorLocation(), m_CurrentHitResultRight->Location);
		return leftRayLength >= rightRayLength;
	});
	selectLeftOrRightNode->AddChild(sequenceNodeDriveRight,
		[this](){
			float leftRayLength = FVector::Dist(GetActorLocation(), m_CurrentHitResultLeft->Location);
			float rightRayLength = FVector::Dist(GetActorLocation(), m_CurrentHitResultRight->Location);
		return rightRayLength > leftRayLength;
	});
	selectNode->AddChild(selectLeftOrRightNode,
	[this](){
		if(!m_Turning)
		{
			m_Turning = true;
			m_EvaluateNPC->HitBarrier();
		}
		return !isSeeingRoadBoth(*m_CurrentLeftMaterial.Get(), *m_CurrentRightMaterial.Get());
	});
	return selectNode;
}