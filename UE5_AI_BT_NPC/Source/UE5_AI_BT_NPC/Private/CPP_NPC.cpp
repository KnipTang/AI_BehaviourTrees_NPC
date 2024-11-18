#include "CPP_NPC.h"
#include "CPP_LeafWalk.h"
#include "CPP_BehaviourTree.h"

ACPP_NPC::ACPP_NPC()
{
	PrimaryActorTick.bCanEverTick = true;
	CPP_LeafWalk* rootNode = new CPP_LeafWalk(this);
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

