#include "CPP_NPC.h"
#include "CPP_LeafWalk.h"
#include "CPP_SequenceNode.h"
#include "CPP_SelectorNode.h"
#include "CPP_BehaviourTree.h"

bool isTrue()
{
	return true;
}

bool isFalse()
{
	return false;
}


ACPP_NPC::ACPP_NPC()
{
	PrimaryActorTick.bCanEverTick = true;
	CPP_SequenceNode* rootNode = new CPP_SequenceNode(this);
	CPP_SelectorNode* selectNode = new CPP_SelectorNode(this);
	CPP_LeafWalk* leafNode1 = new CPP_LeafWalk(this);
	CPP_LeafWalk* leafNode2 = new CPP_LeafWalk(this);
	CPP_LeafWalk* leafNode3 = new CPP_LeafWalk(this);
	selectNode->AddChild(leafNode1, isTrue);
	selectNode->AddChild(leafNode2, isTrue);
	selectNode->AddChild(leafNode3, isFalse);
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
	
	m_BehaviourTree->ExecuteTree();
}

void ACPP_NPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

