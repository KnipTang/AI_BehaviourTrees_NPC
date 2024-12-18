#pragma once

#include "CoreMinimal.h"

class CPP_BaseNode;
class CPP_ControlNode;

class UE5_AI_BT_NPC_API CPP_BehaviourTree
{
public:
	CPP_BehaviourTree(CPP_BaseNode* rootNode);
	CPP_BehaviourTree();
	~CPP_BehaviourTree();

	void Init();

	void SetRootNode(CPP_BaseNode* rootNode) { m_RootNode = rootNode; };
	
	void ExecuteTree();
	
	void AddChild(CPP_ControlNode* parent ,CPP_BaseNode* child);
	void RemoveChild(CPP_ControlNode* parent, CPP_BaseNode* child);
private:
	CPP_BaseNode* m_RootNode;
	bool m_FirstTimeExecuting;
};
