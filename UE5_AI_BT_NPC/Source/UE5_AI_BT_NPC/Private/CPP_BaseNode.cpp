#include "CPP_BaseNode.h"
#include "CPP_NPC.h"

CPP_BaseNode::CPP_BaseNode(ACPP_NPC* npc, int type) :
	m_NPC(npc),
	m_NodeType(type)
{
}

CPP_BaseNode::~CPP_BaseNode()
{
}
