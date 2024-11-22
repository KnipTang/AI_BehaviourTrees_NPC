#pragma once

#include "CoreMinimal.h"
#include "CPP_LeafNode.h"

class UE5_AI_BT_NPC_API CPP_LeafDriveLeft final : public CPP_LeafNode
{
public:
	CPP_LeafDriveLeft(ACPP_NPC* npc);
	~CPP_LeafDriveLeft();
	
	void ExecuteNode() override;
};
