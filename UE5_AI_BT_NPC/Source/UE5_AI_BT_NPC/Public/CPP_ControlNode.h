#pragma once

#include "CoreMinimal.h"
#include "CPP_BaseNode.h"

class UE5_AI_BT_NPC_API CPP_ControlNode : public CPP_BaseNode
{
public:
	CPP_ControlNode(ACPP_NPC* npc);
	~CPP_ControlNode();

	virtual void ExecuteNode() override = 0;
	
	void AddChild(CPP_BaseNode* child);
	void RemoveChild(CPP_BaseNode* child);
private:
	TArray<CPP_BaseNode*> m_Children;
};
