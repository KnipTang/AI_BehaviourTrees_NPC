#include "CPP_BehaviourTree.h"
#include "CPP_BaseNode.h"
#include "CPP_ControlNode.h"

CPP_BehaviourTree::CPP_BehaviourTree(CPP_BaseNode* rootNode) :
	m_RootNode(rootNode)
{
}

CPP_BehaviourTree::CPP_BehaviourTree()
{
}

CPP_BehaviourTree::~CPP_BehaviourTree()
{
}

void CPP_BehaviourTree::ExecuteTree()
{
	m_RootNode->ExecuteNode();
}

void CPP_BehaviourTree::AddChild(CPP_ControlNode* parent, CPP_BaseNode* child)
{
	parent->AddChild(child);
}

void CPP_BehaviourTree::RemoveChild(CPP_ControlNode* parent, CPP_BaseNode* child)
{
	parent->RemoveChild(child);
}
