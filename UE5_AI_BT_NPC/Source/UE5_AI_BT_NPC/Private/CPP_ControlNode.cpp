#include "CPP_ControlNode.h"

CPP_ControlNode::CPP_ControlNode(ACPP_NPC* npc, FString name) :
	CPP_BaseNode(npc, name)
{
	m_LastSelectedNode = nullptr;
}

CPP_ControlNode::~CPP_ControlNode()
{
}

void CPP_ControlNode::BeginNode()
{
	if(m_BeginNodeFunction)
			m_BeginNodeFunction();
}

void CPP_ControlNode::EndNode()
{
	if(m_EndNodeFunction)
		m_EndNodeFunction();
}

void CPP_ControlNode::ChangeExecutionNode(CPP_BaseNode* newNode)
{
	if(m_LastSelectedNode == nullptr)
	{
		newNode->BeginNode();
		m_LastSelectedNode = newNode;
	}
	else if(m_LastSelectedNode->m_NodeName != newNode->m_NodeName)
	{
		m_LastSelectedNode->EndNode();
		newNode->BeginNode();
		m_LastSelectedNode = newNode;
	}
}
