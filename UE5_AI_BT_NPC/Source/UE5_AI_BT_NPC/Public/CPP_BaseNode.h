#pragma once

#include "CoreMinimal.h"

class ACPP_NPC;

class UE5_AI_BT_NPC_API CPP_BaseNode
{
public:
	CPP_BaseNode(ACPP_NPC* npc);
	~CPP_BaseNode();

	virtual void ExecuteNode() = 0;

public:
	TWeakObjectPtr<ACPP_NPC> m_NPC;
private:
};
