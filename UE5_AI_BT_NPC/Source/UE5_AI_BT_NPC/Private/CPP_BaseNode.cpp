#include "CPP_BaseNode.h"
#include "CPP_NPC.h"

CPP_BaseNode::CPP_BaseNode(ACPP_NPC* npc, FString nodeName) :
	m_NPC(npc),
	m_NodeName(nodeName)
{
}

CPP_BaseNode::~CPP_BaseNode()
{
}
