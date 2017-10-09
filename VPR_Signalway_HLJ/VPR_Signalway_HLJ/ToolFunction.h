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

long Tool_GetFileSize(const char *FileName);

bool PingIPaddress(const char* IpAddress);