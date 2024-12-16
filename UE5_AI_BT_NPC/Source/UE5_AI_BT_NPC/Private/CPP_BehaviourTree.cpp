#include "CPP_BehaviourTree.h"
#include "CPP_BaseNode.h"
#include "CPP_ControlNode.h"

CPP_BehaviourTree::CPP_BehaviourTree(CPP_BaseNode* rootNode) :
	m_RootNode(rootNode)
{
	Init();
}

CPP_BehaviourTree::CPP_BehaviourTree()
{
	Init();
}

CPP_BehaviourTree::~CPP_BehaviourTree()
{
}

void CPP_BehaviourTree::Init()
{
	m_FirstTimeExecuting = true;
}

void CPP_BehaviourTree::ExecuteTree()
{
	if(m_RootNode != nullptr)
	{
		if(m_FirstTimeExecuting)
		{
			m_RootNode->BeginNode();
			m_FirstTimeExecuting = false;
		}
		m_RootNode->ExecuteNode();
	}
}

void CPP_BehaviourTree::AddChild(CPP_ControlNode* parent, CPP_BaseNode* child)
{
	if(child != nullptr && parent != nullptr)
		parent->AddChild(child);
}

void CPP_BehaviourTree::RemoveChild(CPP_ControlNode* parent, CPP_BaseNode* child)
{
	if(child != nullptr && parent != nullptr)
		parent->RemoveChild(child);
}
