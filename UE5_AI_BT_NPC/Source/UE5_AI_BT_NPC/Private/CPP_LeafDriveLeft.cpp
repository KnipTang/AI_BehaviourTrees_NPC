#include "CPP_LeafDriveLeft.h"
#include "CPP_NPC.h"

CPP_LeafDriveLeft::CPP_LeafDriveLeft(ACPP_NPC* npc) :
	CPP_LeafNode(npc)
{
}

CPP_LeafDriveLeft::~CPP_LeafDriveLeft()
{
}

void CPP_LeafDriveLeft::ExecuteNode()
{
	//Right = pos X // Left = neg X
	FVector leftDir = m_NPC->GetActorRightVector();
	FVector forwardDir = m_NPC->GetActorForwardVector();
	FVector movementDir = forwardDir + leftDir;

	movementDir.Normalize();
	m_NPC->AddMovementInput(forwardDir);
}
