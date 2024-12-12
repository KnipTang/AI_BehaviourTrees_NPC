// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_LeafWalk.h"
#include "CPP_NPC.h"

CPP_LeafWalk::CPP_LeafWalk(ACPP_NPC* npc) :
	CPP_LeafNode(npc, 3)
{
}

CPP_LeafWalk::~CPP_LeafWalk()
{
}

void CPP_LeafWalk::BeginNode()
{
	UE_LOG(LogTemp, Log, TEXT("Begin Walk"));
}

void CPP_LeafWalk::ExecuteNode()
{
	FVector forwardDir = m_NPC->GetActorForwardVector();
	m_NPC->AddMovementInput(forwardDir, 1);
}

void CPP_LeafWalk::EndNode()
{
	UE_LOG(LogTemp, Log, TEXT("End walk"));
}