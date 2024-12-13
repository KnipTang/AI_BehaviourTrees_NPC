#pragma once

#include "CoreMinimal.h"
#include "CPP_BaseNode.h"

class UE5_AI_BT_NPC_API CPP_ControlNode : public CPP_BaseNode
{
public:
	CPP_ControlNode(ACPP_NPC* npc, int type);
	~CPP_ControlNode();

	virtual void BeginNode() override;
	virtual void EndNode() override;
	
	void AddChild(CPP_BaseNode* child) {};
	void RemoveChild(CPP_BaseNode* child) {};

	void SetBeginNodeFunctionallity(const TFunction<void()>& function) { m_BeginNodeFunction = function; }
	void SetEndNodeFunctionallity(const TFunction<void()>& function) { m_EndNodeFunction = function; }
protected:
	void ChangeExecutionNode(CPP_BaseNode* newNode);
protected:
	TArray<CPP_BaseNode*> m_Children;

	CPP_BaseNode* m_LastSelectedNode;

	TFunction<void()> m_BeginNodeFunction;
	TFunction<void()> m_EndNodeFunction;
};
