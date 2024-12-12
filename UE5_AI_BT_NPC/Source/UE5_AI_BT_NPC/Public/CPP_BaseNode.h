#pragma once

#include "CoreMinimal.h"

class ACPP_NPC;

class UE5_AI_BT_NPC_API CPP_BaseNode
{
public:
	CPP_BaseNode(ACPP_NPC* npc, int type);
	virtual ~CPP_BaseNode();

	virtual void BeginNode() {};
	virtual void ExecuteNode() {};
	virtual void EndNode() {};

public:
	TWeakObjectPtr<ACPP_NPC> m_NPC;
	int m_NodeType = 0;
};
