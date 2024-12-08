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

int ACPP_NPC::NPC_IS_COUNT = 0;

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

	m_EvaluateNPC->ResetFile();
	
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = m_Speed;
	}
}

void ACPP_NPC::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	NPC_IS_COUNT = 0;
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
}

void ACPP_NPC::SetNPCType(NPCType npcType)
{
	switch (npcType)
	{
	case NPCType::Basic2Lines:
		m_BehaviourTree->SetRootNode(NPCtype_Basic2Line());
		break;
	case NPCType::MiddleDriver:
		m_BehaviourTree->SetRootNode(NPCtype_MiddleDriver());
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
			HitResult->Location,
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

void ACPP_NPC::Finished(bool finish)
{
	FString content =
		TEXT("ID: ") + FString::FromInt(NPC_ID) +
		TEXT("\tFINISHED?: ") + FString::FromInt(finish) +
		TEXT("\tTRACK TIME: ") + FString::FromInt(m_EvaluateNPC->GetTrackTime()) +
		TEXT("\tBARRIER HITS: ") + FString::FromInt(m_EvaluateNPC->GetHitBarrier()) +
		TEXT("\tROTATION ANGLE: ") + FString::FromInt(m_RotationAngle) +
		TEXT("\tSPEED: ") + FString::FromInt(m_Speed) +

		TEXT("\n");
	
	m_EvaluateNPC->WriteDataToFile(content);
}

CPP_BaseNode* ACPP_NPC::NPCtype_Basic2Line()
{
	CPP_SelectorNode* selectNode = new CPP_SelectorNode(this);
	CPP_SequenceNode *sequenceNodeDriveleft = new CPP_SequenceNode(this);
	CPP_SequenceNode *sequenceNodeDriveRight = new CPP_SequenceNode(this);
	CPP_LeafWalk* walkLeaf = new CPP_LeafWalk(this);
	CPP_LeafDriveLeft* driveLeftLeaf = new CPP_LeafDriveLeft(this);
	CPP_LeafDriveRight* driveRightLeaf = new CPP_LeafDriveRight(this);
	
	UE_LOG(LogTemp, Warning, TEXT("TEST"));

	sequenceNodeDriveleft->AddChild(walkLeaf);
	sequenceNodeDriveleft->AddChild(driveLeftLeaf);
	sequenceNodeDriveRight->AddChild(walkLeaf);
	sequenceNodeDriveRight->AddChild(driveRightLeaf);
	
	selectNode->AddChild(walkLeaf,
		[this](){
			if(m_Turning)
			{
				m_Turning = false;
			}

			return isSeeingRoadBoth(m_CurrentLeftMaterial, m_CurrentRightMaterial);
		});
	selectNode->AddChild(sequenceNodeDriveleft,
	[this](){
		if(!m_Turning)
		{
			m_Turning = true;
			m_EvaluateNPC->HitBarrier();
		}
		return !isSeeingRoad(m_CurrentRightMaterial);
	});
	selectNode->AddChild(sequenceNodeDriveRight,
	[this](){
		if(!m_Turning)
		{
			m_Turning = true;
			m_EvaluateNPC->HitBarrier();
		}
		return !isSeeingRoad(m_CurrentLeftMaterial);
	});

	return selectNode;
}

CPP_BaseNode* ACPP_NPC::NPCtype_MiddleDriver()
{
	CPP_SelectorNode* selectNode = new CPP_SelectorNode(this);
	CPP_SequenceNode *sequenceNodeDriveleft = new CPP_SequenceNode(this);
	CPP_SequenceNode *sequenceNodeDriveRight = new CPP_SequenceNode(this);
	CPP_LeafWalk* walkLeaf = new CPP_LeafWalk(this);
	CPP_LeafDriveLeft* driveLeftLeaf = new CPP_LeafDriveLeft(this);
	CPP_LeafDriveRight* driveRightLeaf = new CPP_LeafDriveRight(this);

	sequenceNodeDriveleft->AddChild(driveLeftLeaf);
	sequenceNodeDriveleft->AddChild(walkLeaf);
	sequenceNodeDriveRight->AddChild(driveRightLeaf);
	sequenceNodeDriveRight->AddChild(walkLeaf);
	
	float CurrentTurn = 0.0f;
	
	selectNode->AddChild(walkLeaf,
	[this, &CurrentTurn](){
		if (m_CurrentHitResultLeft.IsSet() && m_CurrentHitResultRight.IsSet())
		{
			CurrentTurn = 0.f;
			
			constexpr int offset = 100;
			float leftDistance = m_CurrentHitResultLeft.GetValue().Distance;
			float rightDistance = m_CurrentHitResultRight.GetValue().Distance;
			UE_LOG(LogTemp, Display, TEXT("leftDistance: %f"), leftDistance);
			UE_LOG(LogTemp, Display, TEXT("rightDistance: %f"), rightDistance);
			return FMath::Abs(leftDistance - rightDistance) <= offset;
		}
		return false;
	});
	selectNode->AddChild(sequenceNodeDriveleft,
	[this, &CurrentTurn](){
		if (m_CurrentHitResultLeft.IsSet() && m_CurrentHitResultRight.IsSet())
		{
			float leftDistance = m_CurrentHitResultLeft.GetValue().Distance;
			float rightDistance = m_CurrentHitResultRight.GetValue().Distance;

			CurrentTurn -= 15;
			
			return leftDistance > rightDistance && CurrentTurn > -30;
		}
		return false;
		});
	selectNode->AddChild(sequenceNodeDriveRight,
	[this, &CurrentTurn](){
		  if (m_CurrentHitResultLeft.IsSet() && m_CurrentHitResultRight.IsSet())
		  {
			  float leftDistance = m_CurrentHitResultLeft.GetValue().Distance;
			  float rightDistance = m_CurrentHitResultRight.GetValue().Distance;

		  	  CurrentTurn += 15;
		  	
			  return rightDistance > leftDistance && CurrentTurn < 30;
		  }
		  return false;
	});

	return selectNode;
}