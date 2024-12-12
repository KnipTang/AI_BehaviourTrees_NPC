#pragma once

#include "CoreMinimal.h"
#include "CPP_BaseNode.h"

class UE5_AI_BT_NPC_API CPP_LeafNode : public CPP_BaseNode
{
public:
	CPP_LeafNode(ACPP_NPC* npc, int type);
	~CPP_LeafNode();
};
