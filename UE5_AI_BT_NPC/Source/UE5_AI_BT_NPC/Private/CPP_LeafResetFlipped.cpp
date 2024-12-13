// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_LeafResetFlipped.h"
#include "CPP_NPC.h"

CPP_LeafResetFlipped::CPP_LeafResetFlipped(ACPP_NPC* npc, FString name) :
	CPP_LeafNode(npc, name)
{
}

CPP_LeafResetFlipped::~CPP_LeafResetFlipped()
{
}

void CPP_LeafResetFlipped::BeginNode()
{
	FRotator actorsRotation = m_NPC->GetActorRotation();
	FRotator desiredRotation = FRotator(0, actorsRotation.Pitch, actorsRotation.Yaw);
	m_NPC->SetActorRotation(desiredRotation);
}
