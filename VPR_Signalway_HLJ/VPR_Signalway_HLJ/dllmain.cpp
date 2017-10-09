// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣
#include "stdafx.h"
#include "Camera6467.h"
#include "coredump/MiniDumper.h"


bool  g_bLogEnable = false;
int g_iBackupCount = 1;
CRITICAL_SECTION g_csDLL;
CMiniDumper g_MiniDumper(true);

//Camera6467* g_CameraArray[CAM_COUNT];

bool g_ReadConfig();
void g_WriteConfig();
bool g_IsFileExist( const char* FilePath );
long g_GetFileSize(const char *FileName);
void g_WriteLog(const char*);
void g_ReadKeyValueFromConfigFile(const char* nodeName, const char* keyName, char* keyValue, int bufferSize);



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
        //for (int i = 0; i < CAM_COUNT; i++)
        //{
        //    g_CameraArray[i] = NULL;
        //}
		g_ReadConfig();
		InitializeCriticalSection(&g_csDLL);		
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
        //for (int i = 0; i < CAM_COUNT; i++)
        //{
        //    if (g_CameraArray[i])
        //    {
        //        delete g_CameraArray[i];
        //        g_CameraArray[i] = NULL;
        //    }
        //}
		g_WriteConfig();
		DeleteCriticalSection(&g_csDLL);

		break;
	}
	return TRUE;
}


long g_GetFileSize(const char *FileName)
{
	//FILE* tmpFile = fopen(FileName, "rb");
	FILE* tmpFile = NULL;
	fopen_s(&tmpFile, FileName, "rb");
	if(tmpFile)
	{
		fseek(tmpFile, 0, SEEK_END);
		long fileSize = ftell(tmpFile);
		fclose(tmpFile);
		tmpFile = NULL;
		return fileSize;
	}
	else
	{
		//"open file failed.";
		return 0;
	}
}

bool g_IsFileExist( const char* FilePath )
{
	if (FilePath == NULL)
	{
		return false;
	}
	FILE* tempFile = NULL;
	bool bRet = false;
	//tempFile = fopen(FilePath, "r");
	fopen_s(&tempFile, FilePath, "r");
	if (tempFile)
	{
		bRet = true;
		fclose(tempFile);
		tempFile = NULL;
	}
	return bRet;
}

bool g_ReadConfig()
{
	char FileName[MAX_PATH];
	GetModuleFileNameA(NULL, FileName, MAX_PATH-1);

	PathRemoveFileSpecA(FileName);
	char iniFileName[MAX_PATH] = {0};
	char iniDeviceInfoName[MAX_PATH] = {0};
	strcat_s(iniFileName, FileName);
	strcat_s(iniFileName,"\\XLW_Plate.ini");

	//��ȡ�ɿ��������ļ�
	int iLogEnable =  GetPrivateProfileIntA("Log", "Enable", 0, iniFileName);
	if (iLogEnable == 0 )
	{
		g_bLogEnable = false;
	}
	else
	{
		g_bLogEnable = true;
	}
	g_iBackupCount = GetPrivateProfileIntA("Log", "BackupCount", 1, iniFileName);
	return true;
}

void g_WriteLog(const char* chLog)
{
	g_ReadConfig();
	if (!g_bLogEnable)
	{
		return;
	}
	//ȡ�õ�ǰ�ľ�ȷ�����ʱ��
	static time_t starttime = time(NULL);
	static DWORD starttick = GetTickCount(); 
	DWORD dwNowTick = GetTickCount() - starttick;
	time_t nowtime = starttime + (time_t)(dwNowTick / 1000);
	//struct tm *pTM = localtime(&nowtime);
	struct tm pTM;
	localtime_s(&pTM, &nowtime);
	DWORD dwMS = dwNowTick % 1000;

	const int MAXPATH = 260;

	TCHAR szFileName[ MAXPATH] = {0};
	GetModuleFileName(NULL, szFileName, MAXPATH);	//ȡ�ð�����������ȫ·��
	PathRemoveFileSpec(szFileName);				//ȥ��������

	char chLogPath[MAXPATH] = {0};
	sprintf_s(chLogPath, "%s\\XLWLog\\%d-%02d-%02d\\", szFileName, pTM.tm_year + 1900, pTM.tm_mon +1, pTM.tm_mday);
	MakeSureDirectoryPathExists(chLogPath);

	char chLogFileName[MAXPATH] = {0};
	sprintf_s(chLogFileName, "%s\\XLW_Plate.log", chLogPath);

	FILE *file = NULL;
	//file = fopen(chLogFileName, "a+");
	 fopen_s(&file,chLogFileName, "a+");
	if (file)
	{
		fprintf(file,"%04d-%02d-%02d %02d:%02d:%02d:%03d [Version:%s]: %s\n",  pTM.tm_year + 1900, pTM.tm_mon+1, pTM.tm_mday,
			pTM.tm_hour, pTM.tm_min, pTM.tm_sec, dwMS, DLL_VERSION, chLog);
		fclose(file);
		file = NULL;
	}
}

void g_WriteConfig()
{
	char FileName[MAX_PATH];
	GetModuleFileNameA(NULL, FileName, MAX_PATH-1);

	PathRemoveFileSpecA(FileName);
	char iniFileName[MAX_PATH] = {0};
	char iniDeviceInfoName[MAX_PATH] = {0};
	strcat_s(iniFileName, FileName);
	strcat_s(iniFileName,"\\XLW_Plate.ini");

	char chTemp[260] = {0};
	//sprintf_s(chTemp, "%d", g_iBackupCount);
	//WritePrivateProfileStringA("Log", "BackupCount", chTemp, iniFileName);

	memset(chTemp, 0 , sizeof(chTemp));
	sprintf_s(chTemp, "%d", g_bLogEnable);
	WritePrivateProfileStringA("Log", "Enable", chTemp, iniFileName);
}

void g_ReadKeyValueFromConfigFile(const char* nodeName, const char* keyName, char* keyValue, int bufferSize)
{
	if (strlen(keyValue) > bufferSize)
	{
		return;
	}
	char FileName[MAX_PATH];
	GetModuleFileNameA(NULL, FileName, MAX_PATH-1);

	PathRemoveFileSpecA(FileName);
	char iniFileName[MAX_PATH] = {0};
	char iniDeviceInfoName[MAX_PATH] = {0};
	strcat_s(iniFileName, FileName);
	strcat_s(iniFileName,"\\XLW_Plate.ini");

	GetPrivateProfileStringA(nodeName, keyName, "", keyValue, bufferSize, iniFileName);

	WritePrivateProfileStringA(nodeName, keyName, keyValue, iniFileName);
};