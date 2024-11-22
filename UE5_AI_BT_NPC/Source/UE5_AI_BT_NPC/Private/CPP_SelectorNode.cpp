#include "CPP_SelectorNode.h"

CPP_SelectorNode::CPP_SelectorNode(ACPP_NPC* npc) :
	CPP_BaseNode(npc)
{
}

CPP_SelectorNode::~CPP_SelectorNode()
{
}

void CPP_SelectorNode::ExecuteNode()
{
	int i = 0;
	for (auto&& child : m_Children)
	{
		bool conditionResult = child.Value();
	
		if(conditionResult)
		{
			child.Key->ExecuteNode();
			return;
		}

		i++;
	}
}



void CPP_SelectorNode::RemoveChild(CPP_BaseNode* child)
{
	if(child != nullptr)
	{
		m_Children.Remove(child);
	}
}

