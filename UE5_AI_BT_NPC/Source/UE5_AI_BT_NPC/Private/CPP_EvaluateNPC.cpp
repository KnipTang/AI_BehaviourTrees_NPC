#include "CPP_EvaluateNPC.h"

CPP_EvaluateNPC::CPP_EvaluateNPC() :
m_TimeTrackCompleted{},
m_TimeOffTrack{},
m_HitBarrier{}
{
}

CPP_EvaluateNPC::~CPP_EvaluateNPC()
{
}

void CPP_EvaluateNPC::AddTrackTimer(float time)
{
	m_TimeTrackCompleted += time;
	UE_LOG(LogTemp, Log, TEXT("Track Time: Sec=%f"), m_TimeTrackCompleted);
}

void CPP_EvaluateNPC::AddOffTrackTimer(float time)
{
	m_TimeOffTrack += time;
}
