#pragma once

#include "CoreMinimal.h"
#include "CPP_BaseNode.h"
#include "Containers/Map.h"

class UE5_AI_BT_NPC_API CPP_SelectorNode : public CPP_BaseNode
{
public:
	CPP_SelectorNode(ACPP_NPC* npc);
	~CPP_SelectorNode();
	
	void ExecuteNode() override;
	
	void AddChild(CPP_BaseNode* child, TFunction<bool()> childCondition)
	{
		if (child != nullptr)
		{
			m_Children.Emplace(child, childCondition);
		}
	}
	void RemoveChild(CPP_BaseNode* child);
private:
	using BaseAndCondition = TMap<CPP_BaseNode*, TFunction<bool()>>;
	BaseAndCondition m_Children;
};
