#pragma once

#include "CoreMinimal.h"
#include "CPP_LeafNode.h"

class UE5_AI_BT_NPC_API CPP_LeafDriveRight final : public CPP_LeafNode
{
public:
	CPP_LeafDriveRight(ACPP_NPC* npc, FString name);
	~CPP_LeafDriveRight();
	
	void ExecuteNode() override;
};
