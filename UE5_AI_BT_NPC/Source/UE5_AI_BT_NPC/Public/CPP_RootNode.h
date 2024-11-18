// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_BaseNode.h"

/**
 * 
 */
class UE5_AI_BT_NPC_API CPP_RootNode : public CPP_BaseNode
{
public:
	CPP_RootNode(ACPP_NPC* npc);
	~CPP_RootNode();

	void ExecuteNode() override;
};
