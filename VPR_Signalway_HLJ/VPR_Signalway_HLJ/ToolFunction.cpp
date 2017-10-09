#include "stdafx.h"
#include "ToolFunction.h"
#include <string>

TiXmlElement SelectElementByName(const char* InputInfo, char* pName, int iXMLType)
{
	//注：XMLTYPE 为1时，InputInfo为XML路径，当为2时,InputInfo为二进制文件内容
	TiXmlDocument cXmlDoc;
	TiXmlElement* pRootElement = NULL;
	if (iXMLType == 1)
	{
		if (!cXmlDoc.LoadFile(InputInfo))
		{
			printf("parse XML file failed \n");
			return TiXmlElement("");
		}
	}
	else if (iXMLType == 2)
	{
		if (!cXmlDoc.Parse(InputInfo))
		{
			printf("parse XML failed \n");
			return TiXmlElement("");
		}
	}

	pRootElement = cXmlDoc.RootElement();
	if (NULL == pRootElement)
	{
		printf("no have root Element\n");
		return TiXmlElement("");
	}
	else
	{
		TiXmlElement* pTempElement = NULL;
		pTempElement = ReadElememt(pRootElement, pName);
		if (pTempElement)
		{
			printf("find the Name : %s, Text = %s\n", pTempElement->Value(), pTempElement->GetText());
			return *pTempElement;
		}
		else
		{
			return TiXmlElement("");
		}		
	}
}

TiXmlElement* ReadElememt(TiXmlElement* InputElement, char* pName)
{
	TiXmlElement* ptemp = NULL;
	if (InputElement && 0 == strcmp(pName, InputElement->Value()))
	{
		printf("Find the element :%s \n", InputElement->Value());
		ptemp = InputElement;
		return ptemp;
	}
	else
	{
		printf("%s \n", InputElement->Value());
	}

	TiXmlElement* tmpElement = InputElement;
	if (tmpElement->FirstChildElement())
	{
		ptemp = ReadElememt(tmpElement->FirstChildElement(), pName);
	}
	if (!ptemp)
	{
		tmpElement = tmpElement->NextSiblingElement();
		if (tmpElement)
		{
			ptemp = ReadElememt(tmpElement, pName);
		}
	}
	return ptemp;
}

void g_ReadKeyValueFromConfigFile(const char* IniFileName, const char* nodeName, const char* keyName, char* keyValue, int bufferSize)
{
	if (strlen(keyValue) > bufferSize)
	{
		return;
	}
	char FileName[MAX_PATH];
	GetModuleFileNameA(NULL, FileName, MAX_PATH - 1);

	PathRemoveFileSpecA(FileName);
	char iniFileName[MAX_PATH] = { 0 };
	char iniDeviceInfoName[MAX_PATH] = { 0 };
	MY_SPRINTF(iniFileName, "%s\\%s", FileName, IniFileName);



	GetPrivateProfileStringA(nodeName, keyName, "0", keyValue, bufferSize, iniFileName);

	WritePrivateProfileStringA(nodeName, keyName, keyValue, iniFileName);
}

void g_WriteKeyValueFromConfigFile(const char* INIFileName, const char* nodeName, const char* keyName, char* keyValue, int bufferSize)
{
	if (strlen(keyValue) > bufferSize)
	{
		return;
	}
	char FileName[MAX_PATH];
	GetModuleFileNameA(NULL, FileName, MAX_PATH - 1);

	PathRemoveFileSpecA(FileName);
	char iniFileName[MAX_PATH] = { 0 };
	char iniDeviceInfoName[MAX_PATH] = { 0 };
	strcat_s(iniFileName, FileName);
	strcat_s(iniFileName, INIFileName);


	//GetPrivateProfileStringA(nodeName, keyName, "172.18.109.97", keyValue, bufferSize, iniFileName);

	WritePrivateProfileStringA(nodeName, keyName, keyValue, iniFileName);
}

int g_checkIP(const char* p)
{
	int n[4];
	char c[4];
	//if (sscanf(p, "%d%c%d%c%d%c%d%c",
	//	&n[0], &c[0], &n[1], &c[1],
	//	&n[2], &c[2], &n[3], &c[3])
	//	== 7)
	if (sscanf_s(p, "%d%c%d%c%d%c%d%c",
		&n[0], &c[0], 1,
		&n[1], &c[1], 1,
		&n[2], &c[2], 1,
		&n[3], &c[3], 1)
		== 7)
	{
		int i;
		for (i = 0; i < 3; ++i)
		if (c[i] != '.')
			return 0;
		for (i = 0; i < 4; ++i)
		if (n[i] > 255 || n[i] < 0)
			return 0;
        if (n[0] == 0 && n[1] == 0 && n[2] == 0 && n[3] == 0)
		{
            return 0;
		}
		return 1;
	}
	else
		return 0;
}

bool Tool_IsFileExist(const char* FilePath)
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

long Tool_GetFileSize(const char *FileName)
{
	//FILE* tmpFile = fopen(FileName, "rb");
	FILE* tmpFile = NULL;
	fopen_s(&tmpFile, FileName, "rb");
	if (tmpFile)
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

bool PingIPaddress(const char* IpAddress)
{
	//FILE* pfile;
	//char chBuffer[1024] = {0};
	char chCMD[256] = { 0 };
	sprintf_s(chCMD, "ping %s -n 1", IpAddress);
	//std::string strPingResult;
	//pfile = _popen(chCMD, "r");
	//if (pfile != NULL)
	//{
	//	while(fgets(chBuffer, 1024, pfile) != NULL)
	//	{
	//		strPingResult.append(chBuffer);
	//	}
	//}
	//else
	//{
	//	printf("popen failed. \n");
	//	return false;
	//}
	//_pclose(pfile);
	//printf("%s", strPingResult.c_str());
	//if (std::string::npos != strPingResult.find("TTL") || std::string::npos != strPingResult.find("ttl"))
	//{
	//	return true;
	//}
	//else
	//{
	//	return false;
	//}


	char pbuf[1024]; // 缓存  
	DWORD len;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	HANDLE hRead1 = NULL, hWrite1 = NULL;  // 管道读写句柄  
	BOOL b;
	SECURITY_ATTRIBUTES saAttr;

	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = TRUE; // 管道句柄是可被继承的  
	saAttr.lpSecurityDescriptor = NULL;

	// 创建匿名管道，管道句柄是可被继承的  
	b = CreatePipe(&hRead1, &hWrite1, &saAttr, 1024);
	if (!b)
	{
		//MessageBox(hwnd, "管道创建失败。","Information",0);  
		printf("管道创建失败\n");
		return false;
	}

	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE;
	si.hStdOutput = hWrite1; // 设置需要传递到子进程的管道写句柄  


	// 创建子进程，运行ping命令，子进程是可继承的  
	if (!CreateProcess(NULL, chCMD, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
	{
		//itoa(GetLastError(), pbuf, 10); 
		sprintf_s(pbuf, "%d", GetLastError());
		//MessageBox(hwnd, pbuf,"Information",0);
		printf("%s\n", pbuf);
		CloseHandle(hRead1);
		hRead1 = NULL;
		CloseHandle(hWrite1);
		hWrite1 = NULL;
		return false;
	}

	// 写端句柄已被继承，本地则可关闭，不然读管道时将被阻塞  
	CloseHandle(hWrite1);
	hWrite1 = NULL;

	// 读管道内容，并用消息框显示  
	len = 1000;
	DWORD l;

	std::string strInfo;
	while (ReadFile(hRead1, pbuf, len, &l, NULL))
	{
		if (l == 0) break;
		pbuf[l] = '\0';
		//MessageBox(hwnd, pbuf, "Information",0);  
		//printf("Information2:\n%s\n", pbuf);
		strInfo.append(pbuf);
		len = 1000;
	}

	//MessageBox(hwnd, "ReadFile Exit","Information",0);  
	printf("finish ReadFile buffer = %s\n", strInfo.c_str());
	CloseHandle(hRead1);
	hRead1 = NULL;

	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hThread);
	pi.hThread = NULL;
	CloseHandle(pi.hProcess);
	pi.hProcess = NULL;

	if (std::string::npos != strInfo.find("TTL") || std::string::npos != strInfo.find("ttl"))
	{
		return true;
	}
	else
	{
		return false;
	}
}
