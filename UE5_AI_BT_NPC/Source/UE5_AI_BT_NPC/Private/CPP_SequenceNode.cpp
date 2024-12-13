#include "CPP_SequenceNode.h"

CPP_SequenceNode::CPP_SequenceNode(ACPP_NPC* npc, FString name) :
	CPP_ControlNode(npc, name)
{
}

CPP_SequenceNode::~CPP_SequenceNode()
{
}

void CPP_SequenceNode::ExecuteNode()
{
	for (auto& child : m_Children)
	{
		ChangeExecutionNode(child);
		child->ExecuteNode();
	}
}

void CPP_SequenceNode::AddChild(CPP_BaseNode* child)
{
	if(child != nullptr)
		m_Children.Emplace(child);
}

void CPP_SequenceNode::RemoveChild(CPP_BaseNode* child)
{
	if(child != nullptr)
	{
		int32 Index = m_Children.Find(child);
		if (Index != INDEX_NONE)
		{
			m_Children.RemoveAt(Index);
		}
	}
}
