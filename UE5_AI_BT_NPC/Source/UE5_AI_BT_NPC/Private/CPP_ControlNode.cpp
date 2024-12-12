#include "CPP_ControlNode.h"

CPP_ControlNode::CPP_ControlNode(ACPP_NPC* npc, int type) :
	CPP_BaseNode(npc, type)
{
	m_LastSelectedNode = this;
}

CPP_ControlNode::~CPP_ControlNode()
{
}

void CPP_ControlNode::ChangeExecutionNode(CPP_BaseNode* child)
{
	if(m_LastSelectedNode->m_NodeType != child->m_NodeType)
	{
		m_LastSelectedNode->EndNode();
		child->BeginNode();
		m_LastSelectedNode = child;
	}
}