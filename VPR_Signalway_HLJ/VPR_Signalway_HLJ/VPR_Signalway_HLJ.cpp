// VPR_Signalway_HLJ.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "VPR_Signalway_HLJ.h"
#include "Camera6467.h"
#include "ToolFunction.h"

extern bool g_ReadConfig();
extern void g_WriteConfig();
extern bool g_IsFileExist(const char* FilePath);
extern long g_GetFileSize(const char *FileName);
extern void g_WriteLog(const char*);
extern void g_ReadKeyValueFromConfigFile(const char* nodeName, const char* keyName, char* keyValue, int bufferSize);

//extern Camera6467** g_CameraArray;
Camera6467* g_CameraArray[CAM_COUNT];
//td::list<Camera6467* > g_CameraList;
bool g_bIsInit;

void CheckInitCamera();


int XLW_VFR_API VLPR_Init()
{
    CHAR szLog[1024] = { 0 };
    MY_SPRINTF(szLog, "VLPR_Init begin");
    g_WriteLog(szLog);
    for (int i = 0; i < CAM_COUNT; i++)
    {
        g_CameraArray[i] = NULL;
    }
    CheckInitCamera();
    g_WriteLog("VLPR_Init End.");
    return 0;
}

int XLW_VFR_API VLPR_Deinit()
{
    CheckInitCamera();
    g_WriteLog("VLPR_Deinit begin..");
    Camera6467* pCamera = NULL;
    for (int i = 0; i < CAM_COUNT; i++)
    {
        if (g_CameraArray[i])
        {
            delete g_CameraArray[i];
            g_CameraArray[i] = NULL;
        }
    }
    g_WriteLog("VLPR_Deinit finish.");
    return 0;
}

int XLW_VFR_API VLPR_Login(int nType, char* sParas)
{
    CheckInitCamera();
    char chLog[512] = { 0 };
    MY_SPRINTF(chLog, "VLPR_Login, nType =%d, sParas=%s", nType, sParas);
    g_WriteLog(chLog);
    if (nType == 0)
    {
        g_WriteLog("This device supports Network mode only.");
        return -1000;
    }
    if (strlen(sParas) < 8)
    {
        g_WriteLog("the Parameters is invalid, length less than 8.");
        return -1000;
    }
    
    char chDeviceIP[32] = {0};
    std::string strSrc(sParas);
    std::size_t iPos = strSrc.find(",");
    if (iPos != std::string::npos)
    {
        std::string strSub = strSrc.substr(0, iPos);
        MY_SPRINTF(chDeviceIP, "%s", strSub.c_str());
        g_WriteLog(chDeviceIP);
    }
    else
    {
        g_WriteLog("the Parameters is invalid, can`t find IP address.");
        return -1000;
    }
    int iCheckIp = g_checkIP(chDeviceIP);
    if (iCheckIp != 1)
    {
        g_WriteLog("the Parameters is invalid,  IP address is invalid.");
        return -1000;
    }

    Camera6467* pCamera = NULL;
    std::list<Camera6467*>::iterator it;
    bool bFind = false;
    int iIndex = -1;
    for (int i = 0; i < CAM_COUNT; i++)
    {
        if (g_CameraArray[i])
        {
            if (strcmp(g_CameraArray[i]->GetCameraIP(), chDeviceIP) == 0)
            {
                bFind = true;
                iIndex = i;
                g_WriteLog("HVCR_Open, find the camera .");
                break;
            }
        }
    }
    if (!bFind)
    {
        for (int i = 0; i < CAM_COUNT; i++)
        {
            if (!g_CameraArray[i])
            {
                g_CameraArray[i] = new Camera6467();
                g_CameraArray[i]->SetCameraIP(chDeviceIP);
                g_CameraArray[i]->SetCameraIndex(iIndex);
                g_CameraArray[i]->ConnectToCamera();
                iIndex = i;
                break;
            }
        }
        memset(chLog, '\0', sizeof(chLog));
        MY_SPRINTF(chLog, "VLPR_Login end, create camera %s, index = %d", chDeviceIP, iIndex);
    }
    else
    {
        memset(chLog, '\0', sizeof(chLog));
        MY_SPRINTF(chLog, "VLPR_Login end, find camera %s, index = %d", chDeviceIP, iIndex);
    }
    g_WriteLog(chLog);
    return iIndex;
}

int XLW_VFR_API VLPR_Logout(int nHandle)
{
    CheckInitCamera();
    CHAR chLog[1024] = { 0 };
    MY_SPRINTF(chLog, "VLPR_Logout begin, Handle = %d", nHandle);
    g_WriteLog(chLog);

    if (nHandle > CAM_COUNT || nHandle < 0)
    {
        g_WriteLog("parameters is invalid.");
        return -1000;
    }
    if (g_CameraArray[nHandle])
    {
        delete g_CameraArray[nHandle];
        g_CameraArray[nHandle] = NULL;
    }
    g_WriteLog("VLPR_Logout finished.");
    return 0;
}

int XLW_VFR_API VLPR_SetResultCallBack(int nHandle, CBFun_GetRegResult pFunc, void* pUser)
{
    CheckInitCamera();
    CHAR chLog[1024] = { 0 };
    MY_SPRINTF(chLog, "VLPR_SetResultCallBack begin, Handle = %d, CBFun_GetRegResult = %p, pUser = %p", nHandle, pFunc, pUser);
    g_WriteLog(chLog);
    if (nHandle < 0 || nHandle >= CAM_COUNT)
    {
        g_WriteLog("parameters is invalid.");
        return -1000;
    }

    if (g_CameraArray[nHandle])
    {
        g_CameraArray[nHandle]->SetResult_Callback(pFunc, pUser);
        g_WriteLog(" VLPR_SetResultCallBack end ,SetResultCallBack success.");
        return 0;
    }
    else
    {
        g_WriteLog(" VLPR_SetResultCallBack end ,the camera of nHandle is invalid.");
        return -1002;
    }
}

int XLW_VFR_API VLPR_SetStatusCallBack(int nHandle, int nTimeInvl, CBFun_GetDevStatus pFunc, void* pUser)
{
    CheckInitCamera();
    CHAR chLog[1024] = { 0 };
    MY_SPRINTF(chLog, "VLPR_SetStatusCallBack begin, Handle = %d, CBFun_GetDevStatus = %p, pUser = %p", nHandle, pFunc, pUser);
    g_WriteLog(chLog);
    if (nHandle < 0 || nHandle >= CAM_COUNT)
    {
        g_WriteLog("parameters is invalid.");
        return -1000;
    }

    if (g_CameraArray[nHandle])
    {
        g_CameraArray[nHandle]->SetConnectStatus_Callback(pFunc, pUser, nTimeInvl);
        g_WriteLog(" VLPR_SetStatusCallBack end ,set CBFun_GetDevStatus success.");
        return 0;
    }
    else
    {
        g_WriteLog(" VLPR_SetStatusCallBack end ,the camera of nHandle is invalid.");
        return -1002;
    }
}

int XLW_VFR_API VLPR_ManualSnap(int nhandle)
{
    CheckInitCamera();
    CHAR chLog[1024] = { 0 };
    MY_SPRINTF(chLog, "VLPR_ManualSnap begin, Handle = %d", nhandle);
    g_WriteLog(chLog);
    if (nhandle < 0 || nhandle >= CAM_COUNT)
    {
        g_WriteLog("parameters is invalid.");
        return -1000;
    }

    if (g_CameraArray[nhandle] )
    {
        if (g_CameraArray[nhandle]->TakeCapture())
        {
            g_WriteLog(" VLPR_ManualSnap end ,TakeCapture success.");
            return 0;
        }
        else
        {
            g_WriteLog(" VLPR_ManualSnap end ,TakeCapture failed.");
            return -100;
        }       
    }
    else
    {
        g_WriteLog(" VLPR_ManualSnap end ,the camera of nHandle is invalid.");
        return -1002;
    }
}

int XLW_VFR_API VLPR_GetStatus(int nHandle, int* pStatusCode)
{
    CheckInitCamera();
    CHAR chLog[1024] = { 0 };
    int iHandle = nHandle;
    MY_SPRINTF(chLog, "VLPR_GetStatus begin, Handle = %d", iHandle);
    g_WriteLog(chLog);
    if (iHandle < 0 || iHandle >= CAM_COUNT)
    {
        g_WriteLog("parameters is invalid.");
        return -1000;
    }

    if (g_CameraArray[iHandle])
    {
        if ( 0 == g_CameraArray[iHandle]->GetCamStatus())
        {
            *pStatusCode = 0;
            g_WriteLog(" VLPR_GetStatus end ,GetCamStatus success.");
            return 0;
        }
        else
        {
            *pStatusCode = -100;
            g_WriteLog(" VLPR_GetStatus end , camera is disconnect .");
            return 0;
        }
    }
    else
    {
        g_WriteLog(" VLPR_GetStatus end ,the camera of nHandle is invalid.");
        return -1002;
    }
}

int XLW_VFR_API VLPR_GetStatusMsg(int nStatusCode, char* sStatusMsg, int nStatusMsgLen)
{
    CheckInitCamera();
    CHAR chLog[1024] = { 0 };
    MY_SPRINTF(chLog, "VLPR_GetStatusMsg begin, nStatusCode = %d, sStatusMsg = %s , nStatusMsgLen = %d", nStatusCode, sStatusMsg, nStatusMsgLen);
    g_WriteLog(chLog);

    switch (nStatusCode)
    {
    case 0:
        memcpy(sStatusMsg, "正常\0", sizeof("正常\0"));
        break;
    case -100:
        memcpy(sStatusMsg, "设备无响应\0", sizeof("设备无响应\0"));
        break;
    case -1000:
        memcpy(sStatusMsg, "传入参数错误\0", sizeof("传入参数错误\0"));
        break;
    case -1001:
        memcpy(sStatusMsg, "设备被占用\0", sizeof("设备被占用\0"));
        break;
    case -1002:
        memcpy(sStatusMsg, "打开失败\0", sizeof("打开失败\0"));
        break;
    case -2000:
        memcpy(sStatusMsg, "其他错误\0", sizeof("其他错误\0"));
        break;
    default:
        if (nStatusCode >= -2000)
        {
            memcpy(sStatusMsg, "预留\0", sizeof("预留\0"));
        }
        else
        {
            memcpy(sStatusMsg, "未定义\0", sizeof("未定义\0"));
        }
        break;
    }
    //nStatusMsgLen = strlen(sStatusMsg) + 1;
    memset(chLog, '\0', sizeof(chLog));
    MY_SPRINTF(chLog, "VLPR_GetStatusMsg end, nStatusCode = %d, sStatusMsg = %s , nStatusMsgLen = %d", nStatusCode, sStatusMsg, nStatusMsgLen);
    g_WriteLog(chLog);

    return 0;
}

int XLW_VFR_API VLPR_GetVersion(char* sVersion, int nVerLen)
{
    CHAR chLog[1024] = { 0 };
    MY_SPRINTF(chLog, "VLPR_GetVersion begin, sVersion = %s, nVerLen= %d", sVersion, nVerLen);
    g_WriteLog(chLog);

    char chTemp[260] = {0};
    g_ReadKeyValueFromConfigFile("DeviceInfo", "DLLVersion", chTemp, 260);
    if (strlen(chTemp) < 1)
    {
        memcpy(chTemp, "1.0.0.1\0", sizeof("1.0.0.1\0"));
    }
    memcpy(sVersion, chTemp, strlen(chTemp)+1);
    nVerLen = strlen(chTemp) + 1;

    memset(chLog, '\0', sizeof(chLog));
    MY_SPRINTF(chLog, "VLPR_GetVersion end, sVersion = %s, nVerLen= %d", sVersion, nVerLen);
    g_WriteLog(chLog);
    return 0;
}

void CheckInitCamera()
{
    if (!g_bIsInit)
    {
        for (int i = 0; i < CAM_COUNT; i++)
        {
            g_CameraArray[i] = NULL;
        }
        g_bIsInit = true;
    }
}