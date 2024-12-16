// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_LeafScoping.h"

#include "CPP_NPC.h"
#include "Math/UnrealMathUtility.h"

CPP_LeafScoping::CPP_LeafScoping(ACPP_NPC* npc, FString name) :
	CPP_LeafNode(npc, name)
{

}

CPP_LeafScoping::~CPP_LeafScoping()
{
}

void CPP_LeafScoping::ExecuteNode()
{
	m_NPC->m_DownRayMultiplier = FMath::RandRange(0.8f, 2.f);
}