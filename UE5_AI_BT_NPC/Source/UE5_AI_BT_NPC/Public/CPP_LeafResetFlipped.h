// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_LeafNode.h"

/**
 * 
 */
class UE5_AI_BT_NPC_API CPP_LeafResetFlipped : public CPP_LeafNode
{
public:
	CPP_LeafResetFlipped(ACPP_NPC* npc, FString name);
	~CPP_LeafResetFlipped();

	void BeginNode() override;
};
