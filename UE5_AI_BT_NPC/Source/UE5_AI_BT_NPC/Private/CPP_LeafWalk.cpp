// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_LeafWalk.h"

CPP_LeafWalk::CPP_LeafWalk(ACPP_NPC* npc) :
	CPP_LeafNode(npc)
{
}

CPP_LeafWalk::~CPP_LeafWalk()
{
}

void CPP_LeafWalk::ExecuteNode()
{
	UE_LOG(LogTemp, Log, TEXT("working!"));
}
