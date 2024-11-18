#pragma once

#include "CoreMinimal.h"
#include "CPP_BaseNode.h"
#include <functional>

class UE5_AI_BT_NPC_API CPP_SelectorNode : public CPP_BaseNode
{
public:
	CPP_SelectorNode(ACPP_NPC* npc);
	~CPP_SelectorNode();

	void ExecuteNode() override;
	
	void AddChild(CPP_BaseNode* child, TFunction<bool()> childCondition);
	void RemoveChild(CPP_BaseNode* child);
private:
	using BaseAndCondition = std::pair<CPP_BaseNode*, TFunction<bool()>>;
	TArray<BaseAndCondition> m_Children;

};
