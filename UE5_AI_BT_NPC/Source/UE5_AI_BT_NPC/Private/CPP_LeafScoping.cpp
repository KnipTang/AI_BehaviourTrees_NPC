// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_LeafScoping.h"

#include "CPP_NPC.h"
#include "Math/UnrealMathUtility.h"

CPP_LeafScoping::CPP_LeafScoping(ACPP_NPC* npc) :
	CPP_LeafNode(npc, 6)
{
	m_RayIncrement = 0.01f;
}

CPP_LeafScoping::~CPP_LeafScoping()
{
}

void CPP_LeafScoping::ExecuteNode()
{
	if(!m_GoingUp)
	{
		m_NPC->m_DownRayMultiplier -= m_RayIncrement;
		if(m_NPC->m_DownRayMultiplier <= 0.2f) m_GoingUp = true;
	}
	else
	{
		m_NPC->m_DownRayMultiplier += m_RayIncrement;
		if(m_NPC->m_DownRayMultiplier >= 1.f) m_GoingUp = false;
	}
}