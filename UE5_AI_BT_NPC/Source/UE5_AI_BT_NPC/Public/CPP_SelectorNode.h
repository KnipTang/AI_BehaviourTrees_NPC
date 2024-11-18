#pragma once

#include "CoreMinimal.h"
#include "CPP_ControlNode.h"

class UE5_AI_BT_NPC_API CPP_SelectorNode : public CPP_ControlNode
{
public:
	CPP_SelectorNode(ACPP_NPC* npc);
	~CPP_SelectorNode();
};
