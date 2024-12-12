#include "CPP_LeafDriveRight.h"
#include "CPP_NPC.h"

CPP_LeafDriveRight::CPP_LeafDriveRight(ACPP_NPC* npc) :
	CPP_LeafNode(npc, 4)
{
}

CPP_LeafDriveRight::~CPP_LeafDriveRight()
{
}

void CPP_LeafDriveRight::ExecuteNode()
{
	FRotator desiredRotation = m_NPC->GetActorRotation() + FRotator(0, m_NPC->GetRotationAngle(), 0);
	
	m_NPC->SetActorRotation(desiredRotation);
}
