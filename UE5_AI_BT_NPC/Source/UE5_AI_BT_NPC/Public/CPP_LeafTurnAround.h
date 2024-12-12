#pragma once

#include "CoreMinimal.h"
#include "CPP_LeafNode.h"
class UE5_AI_BT_NPC_API CPP_LeafTurnAround final : public CPP_LeafNode
{
public:
	CPP_LeafTurnAround(ACPP_NPC* npc);
	~CPP_LeafTurnAround();

	void BeginNode() override;
};
