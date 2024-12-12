// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_LeafScoping.h"

#include "CPP_NPC.h"
#include "Math/UnrealMathUtility.h"

CPP_LeafScoping::CPP_LeafScoping(ACPP_NPC* npc) :
	CPP_LeafNode(npc, 6)
{
	m_RayIncrement = 0.001f;
}

CPP_LeafScoping::~CPP_LeafScoping()
{
}

void CPP_LeafScoping::BeginNode()
{
	m_UnchangedDownRay = m_NPC->m_DownRayMultiplier;
	m_NPC->m_DownRayMultiplier = m_UnchangedDownRay;
	m_GoingUp = false;
	UE_LOG(LogTemp, Log, TEXT("Ray: %f"), m_NPC->m_DownRayMultiplier);
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

	Wandering();
	
	UE_LOG(LogTemp, Log, TEXT("Ray: %f"), m_NPC->m_DownRayMultiplier);
}

void CPP_LeafScoping::EndNode()
{
	m_NPC->m_DownRayMultiplier = m_UnchangedDownRay;
}

void CPP_LeafScoping::Wandering()
{
	FRotator desiredRotation = m_NPC->GetActorRotation() + FRotator(0, FMath::RandRange(-m_NPC->GetRotationAngle(), m_NPC->GetRotationAngle()), 0);
	m_NPC->SetActorRotation(desiredRotation);
	FVector forwardDir = m_NPC->GetActorForwardVector();
	m_NPC->AddMovementInput(forwardDir, 1);
}