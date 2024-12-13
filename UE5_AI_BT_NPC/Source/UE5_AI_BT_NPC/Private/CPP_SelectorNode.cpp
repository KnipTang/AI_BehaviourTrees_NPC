#include "CPP_SelectorNode.h"

#include "CPP_LeafNode.h"

CPP_SelectorNode::CPP_SelectorNode(ACPP_NPC* npc) :
	CPP_ControlNode(npc, 2)
{
}

CPP_SelectorNode::~CPP_SelectorNode()
{
}

void CPP_SelectorNode::ExecuteNode()
{
	for (auto&& child : m_Children)
	{
		bool conditionResult = child.Value();
	
		if(conditionResult)
		{
			ChangeExecutionNode(child.Key);
			child.Key->ExecuteNode();
			return;
		}
	}
}

void CPP_SelectorNode::RemoveChild(CPP_BaseNode* child)
{
	if(child != nullptr)
	{
		m_Children.Remove(child);
	}
}