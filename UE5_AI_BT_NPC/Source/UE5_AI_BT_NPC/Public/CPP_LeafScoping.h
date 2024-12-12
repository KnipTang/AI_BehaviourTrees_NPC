// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_LeafNode.h"
/**
 * 
 */
class UE5_AI_BT_NPC_API CPP_LeafScoping final : public CPP_LeafNode
{
public:
	CPP_LeafScoping(ACPP_NPC* npc);
	~CPP_LeafScoping();

	void BeginNode() override;
	void ExecuteNode() override;
	void EndNode() override;

private:
	void Wandering();
private:
	float m_UnchangedDownRay;
	float m_RayIncrement;
	bool m_GoingUp;
};
