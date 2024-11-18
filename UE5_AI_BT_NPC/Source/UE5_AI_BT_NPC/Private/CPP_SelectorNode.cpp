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
	for (auto child : m_Children)
	{
		bool conditionResult = child.second();
	
		if(conditionResult)
			child.first->ExecuteNode();
	}
}

void CPP_SelectorNode::AddChild(CPP_BaseNode* child, TFunction<bool()> childCondition)
{
	if(child != nullptr)
	{
		BaseAndCondition newChild = BaseAndCondition(child, childCondition);
		m_Children.Emplace(newChild);
	}
}

void CPP_SelectorNode::RemoveChild(CPP_BaseNode* child)
{
	if(child != nullptr)
	{
		for (int32 Index = 0; Index < m_Children.Num(); ++Index)
		{
			if (m_Children[Index].first == child) 
			{
				m_Children.RemoveAt(Index);
				return;
			}
		}
	}
}

