#include "CPP_LeafTurnAround.h"
#include "CPP_NPC.h"

CPP_LeafTurnAround::CPP_LeafTurnAround(ACPP_NPC* npc, FString name) :
	CPP_LeafNode(npc, name)
{
}

CPP_LeafTurnAround::~CPP_LeafTurnAround()
{
}

void CPP_LeafTurnAround::BeginNode()
{
	SetCurrentNode();
	
	FRotator desiredRotation = m_NPC->GetActorRotation() + FRotator(0, 180, 0);
	m_NPC->SetActorRotation(desiredRotation);
	m_NPC->m_RecordPercentageTrack = m_NPC->m_PercentageTrackCurrent;
}