#include "stdafx.h"
#include "ToolFunction.h"
#include <string>
#include<shellapi.h>

#include <gdiplus.h>
using namespace Gdiplus;
#pragma  comment(lib, "gdiplus.lib")

TiXmlElement SelectElementByName(const char* InputInfo, char* pName, int iXMLType)
{
	//ע��XMLTYPE Ϊ1ʱ��InputInfoΪXML·������Ϊ2ʱ,InputInfoΪ�������ļ�����
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

bool Tool_MakeDir(const char* chImgPath)
{
    if (NULL == chImgPath)
    {
        //WriteLog("the path is null ,Create Dir failed.");
        return false;
    }
    std::string tempFile(chImgPath);
    size_t iPosition = tempFile.rfind("\\");
    std::string tempDir = tempFile.substr(0, iPosition + 1);
    if (MakeSureDirectoryPathExists(tempDir.c_str()))
    {
        return true;
    }
    else
    {
        //WriteLog("Create Dir failed.");
        return false;
    }
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


	char pbuf[1024]; // ����  
	DWORD len;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	HANDLE hRead1 = NULL, hWrite1 = NULL;  // �ܵ���д���  
	BOOL b;
	SECURITY_ATTRIBUTES saAttr;

	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = TRUE; // �ܵ�����ǿɱ��̳е�  
	saAttr.lpSecurityDescriptor = NULL;

	// ���������ܵ����ܵ�����ǿɱ��̳е�  
	b = CreatePipe(&hRead1, &hWrite1, &saAttr, 1024);
	if (!b)
	{
		//MessageBox(hwnd, "�ܵ�����ʧ�ܡ�","Information",0);  
		printf("�ܵ�����ʧ��\n");
		return false;
	}

	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE;
	si.hStdOutput = hWrite1; // ������Ҫ���ݵ��ӽ��̵Ĺܵ�д���  


	// �����ӽ��̣�����ping����ӽ����ǿɼ̳е�  
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

	// д�˾���ѱ��̳У�������ɹرգ���Ȼ���ܵ�ʱ��������  
	CloseHandle(hWrite1);
	hWrite1 = NULL;

	// ���ܵ����ݣ�������Ϣ����ʾ  
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

bool Tool_Img_ScaleJpg(PBYTE pbSrc, int iSrcLen, PBYTE pbDst, DWORD *iDstLen, int iDstWidth, int iDstHeight, int compressQuality)
{
    if (pbSrc == NULL || iSrcLen <= 0)
    {
        return false;
    }
    if (pbDst == NULL || iDstLen == NULL || *iDstLen <= 0)
    {
        return false;
    }
    if (iDstWidth <= 0 || iDstHeight <= 0)
    {
        return false;
    }

    // init gdi+
    ULONG_PTR gdiplusToken = NULL;
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    // ������
    IStream *pstmp = NULL;
    CreateStreamOnHGlobal(NULL, TRUE, &pstmp);
    if (pstmp == NULL)
    {
        GdiplusShutdown(gdiplusToken);
        gdiplusToken = NULL;
        return false;
    }

    // ��ʼ����
    LARGE_INTEGER liTemp = { 0 };
    ULARGE_INTEGER uLiZero = { 0 };
    pstmp->Seek(liTemp, STREAM_SEEK_SET, NULL);
    pstmp->SetSize(uLiZero);

    // ��ͼ���������
    ULONG ulRealSize = 0;
    pstmp->Write(pbSrc, iSrcLen, &ulRealSize);

    // ��������λͼ
    Bitmap bmpSrc(pstmp);
    Bitmap bmpDst(iDstWidth, iDstHeight, PixelFormat24bppRGB);

    // ������ͼ����
    Graphics grDraw(&bmpDst);

    // ��ͼ
    grDraw.DrawImage(&bmpSrc, 0, 0, bmpSrc.GetWidth(), bmpSrc.GetHeight());
    if (Ok != grDraw.GetLastStatus())
    {
        pstmp->Release();
        pstmp = NULL;
        GdiplusShutdown(gdiplusToken);
        gdiplusToken = NULL;
        return false;
    }

    // ���������
    IStream* pStreamOut = NULL;
    if (CreateStreamOnHGlobal(NULL, TRUE, &pStreamOut) != S_OK)
    {
        pstmp->Release();
        pstmp = NULL;
        GdiplusShutdown(gdiplusToken);
        gdiplusToken = NULL;
        return false;
    }

    CLSID jpgClsid;
    Tool_GetEncoderClsid(L"image/jpeg", &jpgClsid);

    // ��ʼ�������
    pStreamOut->Seek(liTemp, STREAM_SEEK_SET, NULL);
    pStreamOut->SetSize(uLiZero);

    // ��λͼ����JPG�ĸ�ʽ���浽�������
    int iQuality = compressQuality % 100;
    EncoderParameters encoderParameters;
    encoderParameters.Count = 1;
    encoderParameters.Parameter[0].Guid = EncoderQuality;
    encoderParameters.Parameter[0].Type = EncoderParameterValueTypeLong;
    encoderParameters.Parameter[0].NumberOfValues = 1;
    encoderParameters.Parameter[0].Value = &iQuality;
    bmpDst.Save(pStreamOut, &jpgClsid, &encoderParameters);
    //bmpDst.Save(pStreamOut, &jpgClsid, 0);

    // ��ȡ�������С
    bool bRet = false;
    ULARGE_INTEGER libNewPos = { 0 };
    pStreamOut->Seek(liTemp, STREAM_SEEK_END, &libNewPos);      // ����ָ��ָ�����λ�ã��Ӷ���ȡ���Ĵ�С 
    if (*iDstLen < (int)libNewPos.LowPart)                     // �û�����Ļ���������
    {
        *iDstLen = libNewPos.LowPart;
        bRet = false;
    }
    else
    {
        pStreamOut->Seek(liTemp, STREAM_SEEK_SET, NULL);                   // ����ָ��ָ��ʼλ��
        pStreamOut->Read(pbDst, libNewPos.LowPart, &ulRealSize);           // ��ת�����JPGͼƬ�������û�
        *iDstLen = ulRealSize;
        bRet = true;
    }


    // �ͷ��ڴ�
    if (pstmp != NULL)
    {
        pstmp->Release();
        pstmp = NULL;
    }
    if (pStreamOut != NULL)
    {
        pStreamOut->Release();
        pStreamOut = NULL;
    }

    GdiplusShutdown(gdiplusToken);
    gdiplusToken = NULL;

    return bRet;
}

int Tool_GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
    UINT  num = 0;          // number of image encoders
    UINT  size = 0;         // size of the image encoder array in bytes

    ImageCodecInfo* pImageCodecInfo = NULL;

    GetImageEncodersSize(&num, &size);
    if (size == 0)
        return -1;  // Failure

    pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
    if (pImageCodecInfo == NULL)
        return -1;  // Failure

    GetImageEncoders(num, size, pImageCodecInfo);

    for (UINT j = 0; j < num; ++j)
    {
        if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
        {
            *pClsid = pImageCodecInfo[j].Clsid;
            free(pImageCodecInfo);
            return j;  // Success
        }
    }
    free(pImageCodecInfo);
    return -1;  // Failure
}

void Tool_ExcuteShellCMD(char* pChCommand)
{
    if (NULL == pChCommand)
    {
        return;
    }
    ShellExecute(NULL, "open", "C:\\WINDOWS\\system32\\cmd.exe", pChCommand, "", SW_HIDE);
}

bool Tool_OverlayStringToImg(unsigned char** pImgsrc, long srcSize,
    unsigned char** pImgDest, long& DestSize,
    wchar_t* DestString, int FontSize,
    int x, int y, int colorR, int colorG, int colorB,
    int compressQuality)
{
    if (!pImgsrc || !pImgDest || srcSize <= 0 || DestSize <= 0)
    {
        //WriteLog("�������Ϊ�Ƿ�ֵ");
        return false;
    }
    if (wcslen(DestString) <= 0 || x < 0 || y < 0)
    {
        //WriteLog("�ַ�������Ϊ0");
        return false;
    }

    //����ͼ��	
    IStream *pSrcStream = NULL;
    IStream *pDestStream = NULL;
    CreateStreamOnHGlobal(NULL, TRUE, &pSrcStream);
    CreateStreamOnHGlobal(NULL, TRUE, &pDestStream);
    if (!pSrcStream || !pDestStream)
    {
        //WriteLog("������ʧ��.");
        return false;
    }
    LARGE_INTEGER liTemp = { 0 };
    pSrcStream->Seek(liTemp, STREAM_SEEK_SET, NULL);
    pSrcStream->Write(*pImgsrc, srcSize, NULL);
    Bitmap bmp(pSrcStream);
    int iImgWith = bmp.GetWidth();
    int iImgHeight = bmp.GetHeight();

    Graphics grp(&bmp);

    SolidBrush brush(Color(colorR, colorG, colorB));
    FontFamily fontFamily(L"����");
    //Gdiplus::Font font(&fontFamily, (REAL)FontSize);
    Gdiplus::Font font(&fontFamily, (REAL)FontSize, FontStyleRegular, UnitPixel);

    RectF layoutRect(x, y, iImgWith - x, 0);
    RectF FinalRect;
    INT codePointsFitted = 0;
    INT linesFitted = 0;
    int strLenth = wcslen(DestString);
    grp.MeasureString(DestString, strLenth, &font, layoutRect, NULL, &FinalRect, &codePointsFitted, &linesFitted);
    grp.DrawString(DestString, -1, &font, FinalRect, NULL, &brush);
    Gdiplus::Status iState = grp.GetLastStatus();
    if (iState == Ok)
    {
        //WriteLog("�ַ����ӳɹ�");
    }
    else
    {
        //char chLog[260] = { 0 };
        //sprintf(chLog, "�ַ�����ʧ�ܣ� ������Ϊ%d", iState);
        //WriteLog(chLog);
    }

    pSrcStream->Seek(liTemp, STREAM_SEEK_SET, NULL);
    pDestStream->Seek(liTemp, STREAM_SEEK_SET, NULL);

    // ��λͼ����JPG�ĸ�ʽ���浽�������
    CLSID jpgClsid;
    Tool_GetEncoderClsid(L"image/jpeg", &jpgClsid);
    int iQuality = compressQuality;
    EncoderParameters encoderParameters;
    encoderParameters.Count = 1;
    encoderParameters.Parameter[0].Guid = EncoderQuality;
    encoderParameters.Parameter[0].Type = EncoderParameterValueTypeLong;
    encoderParameters.Parameter[0].NumberOfValues = 1;
    encoderParameters.Parameter[0].Value = &iQuality;
    bmp.Save(pDestStream, &jpgClsid, &encoderParameters);

    ULARGE_INTEGER uiSize;
    pDestStream->Seek(liTemp, STREAM_SEEK_CUR, &uiSize);
    long iFinalSize = (long)uiSize.QuadPart;
    if (iFinalSize <= DestSize)
    {
        pDestStream->Seek(liTemp, STREAM_SEEK_SET, NULL);
        pDestStream->Read(*pImgDest, iFinalSize, NULL);
        DestSize = iFinalSize;
    }
    else
    {
        DestSize = 0;
        if (pSrcStream)
        {
            pSrcStream->Release();
            pSrcStream = NULL;
        }
        if (pDestStream)
        {
            pDestStream->Release();
            pDestStream = NULL;
        }
        //WriteLog("����ռ䲻�㣬�ַ�����ʧ��");
        return false;
    }

    if (pSrcStream)
    {
        pSrcStream->Release();
        pSrcStream = NULL;
    }
    if (pDestStream)
    {
        pDestStream->Release();
        pDestStream = NULL;
    }
    return true;
}