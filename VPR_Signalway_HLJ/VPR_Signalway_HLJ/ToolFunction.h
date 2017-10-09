#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"


//ͨ���ڵ������Ҳ�������Ӧ�ڵ�
//ע��XMLTYPE Ϊ1ʱ��InputInfoΪXML·������Ϊ2ʱ,InputInfoΪ�������ļ�����
TiXmlElement SelectElementByName(const char* InputInfo, char* pName, int iXMLType);

TiXmlElement* ReadElememt(TiXmlElement* InputElement, char* pName);

void g_ReadKeyValueFromConfigFile(const char* FileName, const char* nodeName, const char* keyName, char* keyValue, int bufferSize);

void g_WriteKeyValueFromConfigFile(const char* FileName, const char* nodeName, const char* keyName, char* keyValue, int bufferSize);

//���IP����Ч��
int g_checkIP(const char* p);

bool Tool_IsFileExist(const char* FilePath);

bool Tool_MakeDir(const char* chImgPath);

long Tool_GetFileSize(const char *FileName);

bool PingIPaddress(const char* IpAddress);

bool Tool_Img_ScaleJpg(PBYTE pbSrc, int iSrcLen, PBYTE pbDst, DWORD *iDstLen, int iDstWidth, int iDstHeight, int compressQuality);

int Tool_GetEncoderClsid(const WCHAR* format, CLSID* pClsid);

void Tool_ExcuteShellCMD(char* pChCommand);

bool Tool_OverlayStringToImg(unsigned char** pImgsrc, long srcSize,
    unsigned char** pImgDest, long& DestSize,
    wchar_t* DestString, int FontSize,
    int x, int y, int colorR, int colorG, int colorB,
    int compressQuality);