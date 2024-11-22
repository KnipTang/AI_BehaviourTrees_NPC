#include "CPP_NPC.h"
#include "CPP_LeafWalk.h"
#include "CPP_SequenceNode.h"
#include "CPP_SelectorNode.h"
#include "CPP_BehaviourTree.h"

bool isTrue()
{
	return true;
}

bool isFalse(bool value)
{
	return value;
}

bool isSeeingRoad(UMaterialInterface& mat)
{
	if(mat.GetName() == "road")
		return true;
	return false;
}

ACPP_NPC::ACPP_NPC()
{
	PrimaryActorTick.bCanEverTick = true;
	CPP_SequenceNode* sequenceNode = new CPP_SequenceNode(this);
	CPP_SelectorNode* selectNode = new CPP_SelectorNode(this);
	CPP_LeafWalk* leafNode1 = new CPP_LeafWalk(this);
	CPP_LeafWalk* leafNode2 = new CPP_LeafWalk(this);
	CPP_LeafWalk* leafNode3 = new CPP_LeafWalk(this);
	sequenceNode->AddChild(leafNode1);
	selectNode->AddChild(sequenceNode, []() { return isFalse(false); });
	selectNode->AddChild(sequenceNode, isTrue);
	//selectNode->AddChild(leafNode2, isTrue);
	//selectNode->AddChild(leafNode3, isFalse);
	m_BehaviourTree = new CPP_BehaviourTree{selectNode};
}

ACPP_NPC::~ACPP_NPC()
{
}

void ACPP_NPC::BeginPlay()
{
	Super::BeginPlay();
}

void ACPP_NPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	SetCurrentLookAtMaterial();
	m_BehaviourTree->ExecuteTree();
}

void ACPP_NPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

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

	return HitMaterial;
}

void ACPP_NPC::SetCurrentLookAtMaterial()
{
	float rayLength = 300.f;
	
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
