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
	//UE_LOG(LogTemp, Log, TEXT("Track Time: Sec=%f"), m_TimeTrackCompleted);
}

void CPP_EvaluateNPC::AddOffTrackTimer(float time)
{
	m_TimeOffTrack += time;
}

void CPP_EvaluateNPC::ResetFile()
{
	FString CurrentPath = FPaths::Combine(FPaths::ProjectDir(), TEXT("Evaluation"), TEXT("NPC_Evaluation.txt"));
	FFileHelper::SaveStringToFile(FString(""), *CurrentPath);
}
 

void CPP_EvaluateNPC::WriteDataToFile(const FString& Content)
{
	FString CurrentPath = FPaths::Combine(FPaths::ProjectDir(), TEXT("Evaluation"), TEXT("NPC_Evaluation.txt"));
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	IFileHandle* FileHandle = PlatformFile.OpenWrite(*CurrentPath, true);
	if (FileHandle)
	{
		const TCHAR* Data = *Content;
		int32 Size = FCString::Strlen(Data) * sizeof(TCHAR);
		FileHandle->Write((const uint8*)Data, Size);
		
		UE_LOG(LogTemp, Log, TEXT("Content Written To: %s"), *CurrentPath);
		
		delete FileHandle;
	}
}
