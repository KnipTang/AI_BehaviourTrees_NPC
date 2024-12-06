#pragma once

#include "CoreMinimal.h"

class UE5_AI_BT_NPC_API CPP_EvaluateNPC
{
public:
	CPP_EvaluateNPC();
	~CPP_EvaluateNPC();

	void AddTrackTimer(float time);

	void AddOffTrackTimer(float time);

	float GetTrackTime() const { return m_TimeTrackCompleted; };

	void HitBarrier() {	m_HitBarrier++; };

	void ResetFile();
	void WriteDataToFile(const FString& Content);
private:
	float m_TimeTrackCompleted;
	float m_TimeOffTrack;
	int m_HitBarrier;
};
