#include "CPP_LeafDriveLeft.h"
#include "CPP_NPC.h"
#include "GameFramework/PawnMovementComponent.h"

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
	FVector rightDir = m_NPC->GetActorRightVector();
	FVector forwardDir = m_NPC->GetActorForwardVector();
	FVector movementDir = forwardDir - rightDir;
	
	movementDir.Normalize();
	m_NPC->AddMovementInput(movementDir);

	FRotator desiredRotation = m_NPC->GetActorRotation() + FRotator(0, -30, 0);
	
	m_NPC->SetActorRotation(desiredRotation);
}
