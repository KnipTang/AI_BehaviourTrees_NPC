#include "CPP_LeafDriveLeft.h"
#include "CPP_NPC.h"

CPP_LeafDriveLeft::CPP_LeafDriveLeft(ACPP_NPC* npc) :
	CPP_LeafNode(npc, 5)
{
}

CPP_LeafDriveLeft::~CPP_LeafDriveLeft()
{
}

void CPP_LeafDriveLeft::ExecuteNode()
{
	FRotator desiredRotation = m_NPC->GetActorRotation() + FRotator(0, -m_NPC->GetRotationAngle(), 0);
	
	m_NPC->SetActorRotation(desiredRotation);
}
