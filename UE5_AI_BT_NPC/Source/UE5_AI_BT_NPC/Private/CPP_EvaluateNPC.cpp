#include "CPP_EvaluateNPC.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFilemanager.h"

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
}

void CPP_EvaluateNPC::AddOffTrackTimer(float time)
{
	m_TimeOffTrack += time;
}

void CPP_EvaluateNPC::HitBarrier()
{
	m_HitBarrier++;
};

void CPP_EvaluateNPC::ResetFile()
{
	FString CurrentPath = FPaths::Combine(FPaths::ProjectDir(), TEXT("Evaluation"), TEXT("NPC_Evaluation.txt"));
	FFileHelper::SaveStringToFile(FString(""), *CurrentPath);
}
 

void CPP_EvaluateNPC::WriteDataToFile(const FString& Content)
{
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	FString FilePath = FPaths::ProjectDir() + TEXT("Evaluation/Output.csv");

	if (PlatformFile.FileExists(*FilePath))
	{
		IFileHandle* FileHandle = PlatformFile.OpenWrite(*FilePath, /*bAppend=*/true);
		if (FileHandle)
		{
			FileHandle->Write((const uint8*)TCHAR_TO_ANSI(*Content), Content.Len());
			delete FileHandle;
		}
	}
}
