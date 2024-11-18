#include "CPP_SequenceNode.h"

CPP_SequenceNode::CPP_SequenceNode(ACPP_NPC* npc) :
	CPP_ControlNode(npc)
{
}

CPP_SequenceNode::~CPP_SequenceNode()
{
}

void CPP_SequenceNode::ExecuteNode()
{
	for (auto& child : m_Children)
	{
		child->ExecuteNode();
	}
}
