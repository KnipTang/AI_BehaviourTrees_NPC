#include "CPP_LeafNode.h"
#include "CPP_NPC.h"

CPP_LeafNode::CPP_LeafNode(ACPP_NPC* npc, FString name) :
	CPP_BaseNode(npc, name)
{
}

CPP_LeafNode::~CPP_LeafNode()
{
}

void CPP_LeafNode::SetCurrentNode()
{
	m_NPC->m_CurrentNode = this;
	m_NPC->GetCurrentNodeName();
}