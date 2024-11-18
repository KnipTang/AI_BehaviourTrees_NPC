#include "CPP_ControlNode.h"

CPP_ControlNode::CPP_ControlNode(ACPP_NPC* npc) :
	CPP_BaseNode(npc)
{
}

CPP_ControlNode::~CPP_ControlNode()
{
}

void CPP_ControlNode::AddChild(CPP_BaseNode* child)
{
	if(child != nullptr)
		m_Children.Emplace(child);
}

void CPP_ControlNode::RemoveChild(CPP_BaseNode* child)
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
