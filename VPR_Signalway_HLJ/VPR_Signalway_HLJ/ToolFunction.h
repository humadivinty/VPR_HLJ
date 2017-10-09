#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"


//通过节点名查找并返回相应节点
//注：XMLTYPE 为1时，InputInfo为XML路径，当为2时,InputInfo为二进制文件内容
TiXmlElement SelectElementByName(const char* InputInfo, char* pName, int iXMLType);

TiXmlElement* ReadElememt(TiXmlElement* InputElement, char* pName);

void g_ReadKeyValueFromConfigFile(const char* FileName, const char* nodeName, const char* keyName, char* keyValue, int bufferSize);

void g_WriteKeyValueFromConfigFile(const char* FileName, const char* nodeName, const char* keyName, char* keyValue, int bufferSize);

//检查IP的有效性
int g_checkIP(const char* p);

bool Tool_IsFileExist(const char* FilePath);

long Tool_GetFileSize(const char *FileName);

bool PingIPaddress(const char* IpAddress);