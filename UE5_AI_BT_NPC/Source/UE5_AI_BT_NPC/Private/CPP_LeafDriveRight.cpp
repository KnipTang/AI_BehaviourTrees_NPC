#include "CPP_LeafDriveRight.h"
#include "CPP_NPC.h"

CPP_LeafDriveRight::CPP_LeafDriveRight(ACPP_NPC* npc) :
	CPP_LeafNode(npc)
{
}

CPP_LeafDriveRight::~CPP_LeafDriveRight()
{
}

void CPP_LeafDriveRight::ExecuteNode()
{
	//Right = pos X // Left = neg X
	FVector rightDir = m_NPC->GetActorRightVector();
	FVector forwardDir = m_NPC->GetActorForwardVector();
	FVector movementDir = forwardDir + rightDir;
	
	movementDir.Normalize();
	m_NPC->AddMovementInput(movementDir);

	FRotator desiredRotation = m_NPC->GetActorRotation() + FRotator(0, 30, 0);
	
	m_NPC->SetActorRotation(desiredRotation);
}
