#include "CPP_NPC.h"
#include "CPP_LeafWalk.h"
#include "CPP_SequenceNode.h"
#include "CPP_BehaviourTree.h"

ACPP_NPC::ACPP_NPC()
{
	PrimaryActorTick.bCanEverTick = true;
	CPP_SequenceNode* rootNode = new CPP_SequenceNode(this);
	CPP_LeafWalk* leafNode1 = new CPP_LeafWalk(this);
	CPP_LeafWalk* leafNode2 = new CPP_LeafWalk(this);
	CPP_LeafWalk* leafNode3 = new CPP_LeafWalk(this);
	rootNode->AddChild(leafNode1);
	rootNode->AddChild(leafNode2);
	rootNode->AddChild(leafNode3);
	m_BehaviourTree = new CPP_BehaviourTree{rootNode};
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
	
	m_BehaviourTree->ExecuteTree();
}

void ACPP_NPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

