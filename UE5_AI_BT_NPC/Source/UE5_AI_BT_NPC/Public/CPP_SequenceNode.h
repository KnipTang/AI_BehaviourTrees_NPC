#pragma once

#include "CoreMinimal.h"
#include "CPP_ControlNode.h"

class UE5_AI_BT_NPC_API CPP_SequenceNode : public CPP_ControlNode
{
public:
	CPP_SequenceNode(ACPP_NPC* npc);
	~CPP_SequenceNode();

	void ExecuteNode() override;
};
