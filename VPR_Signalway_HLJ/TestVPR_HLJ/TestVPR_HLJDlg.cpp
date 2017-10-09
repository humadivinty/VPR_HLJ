
// TestVPR_HLJDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestVPR_HLJ.h"
#include "TestVPR_HLJDlg.h"
#include "afxdialogex.h"
#include "../VPR_Signalway_HLJ/CommonDef_VPR.h"
#include "../VPR_Signalway_HLJ/VPR_Signalway_HLJ.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <Dbghelp.h>
#pragma comment(lib, "Dbghelp.lib")

#ifdef DEBUG
#pragma comment(lib, "../Debug/VPR_Signalway_HLJ.lib")
#else
#pragma comment(lib, "../Release/VPR_Signalway_HLJ.lib")
#endif // DEBUG



// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTestVPR_HLJDlg �Ի���



CTestVPR_HLJDlg::CTestVPR_HLJDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestVPR_HLJDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestVPR_HLJDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestVPR_HLJDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON_Init, &CTestVPR_HLJDlg::OnBnClickedButtonInit)
    ON_BN_CLICKED(IDC_BUTTON_Login, &CTestVPR_HLJDlg::OnBnClickedButtonLogin)
    ON_BN_CLICKED(IDC_BUTTON_Logout, &CTestVPR_HLJDlg::OnBnClickedButtonLogout)
    ON_BN_CLICKED(IDC_BUTTON_Deinit, &CTestVPR_HLJDlg::OnBnClickedButtonDeinit)
    ON_BN_CLICKED(IDC_BUTTON_SetResultCallBack, &CTestVPR_HLJDlg::OnBnClickedButtonSetresultcallback)
    ON_BN_CLICKED(IDC_BUTTON_SetStatusCallBack, &CTestVPR_HLJDlg::OnBnClickedButtonSetstatuscallback)
    ON_BN_CLICKED(IDC_BUTTON_ManualSnap, &CTestVPR_HLJDlg::OnBnClickedButtonManualsnap)
    ON_BN_CLICKED(IDC_BUTTON_GetStatus, &CTestVPR_HLJDlg::OnBnClickedButtonGetstatus)
    ON_BN_CLICKED(IDC_BUTTON_GetStatusMsg, &CTestVPR_HLJDlg::OnBnClickedButtonGetstatusmsg)
    ON_BN_CLICKED(IDC_BUTTON_GetVersion, &CTestVPR_HLJDlg::OnBnClickedButtonGetversion)
END_MESSAGE_MAP()


// CTestVPR_HLJDlg ��Ϣ�������

BOOL CTestVPR_HLJDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTestVPR_HLJDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTestVPR_HLJDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTestVPR_HLJDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestVPR_HLJDlg::OnBnClickedButtonInit()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    int iRet = VLPR_Init();
    char chLog[MAX_PATH] = {0};
    sprintf_s(chLog, "VLPR_Init ����ֵΪ %d", iRet);
    MessageBox(chLog);
}


void CTestVPR_HLJDlg::OnBnClickedButtonLogin()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    CString cstrIP;
    GetDlgItem(IDC_IPADDRESS1)->GetWindowTextA(cstrIP);
    CString strTemp;
    strTemp.Format("%s, 8000, admin, admin", cstrIP);

    int iRet = VLPR_Login(1, strTemp.GetBuffer());
    m_iIndex = iRet;
    strTemp.ReleaseBuffer();

    char chLog[MAX_PATH] = { 0 };
    sprintf_s(chLog, "VLPR_Login, ���� %s,  ����ֵΪ %d, ", strTemp.GetBuffer(), iRet);
    strTemp.ReleaseBuffer();

    MessageBox(chLog);
}


void CTestVPR_HLJDlg::OnBnClickedButtonLogout()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    int iRet = VLPR_Logout(m_iIndex);
    char chLog[MAX_PATH] = { 0 };
    sprintf_s(chLog, "VLPR_Logout , nHandle = %d, ����ֵΪ %d",m_iIndex,  iRet);
    MessageBox(chLog);
}


void CTestVPR_HLJDlg::OnBnClickedButtonDeinit()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    int iRet = VLPR_Deinit();
    char chLog[MAX_PATH] = { 0 };
    sprintf_s(chLog, "VLPR_Deinit ,  ����ֵΪ %d",  iRet);
    MessageBox(chLog);
}


void CTestVPR_HLJDlg::OnBnClickedButtonSetresultcallback()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    int iRet = VLPR_SetResultCallBack(m_iIndex, CBFun_GetRegResult, this);
    char chLog[MAX_PATH] = { 0 };
    sprintf_s(chLog, "VLPR_SetResultCallBack , nHandle = %d, ����ֵΪ %d", m_iIndex, iRet);
    MessageBox(chLog);
}


void CTestVPR_HLJDlg::OnBnClickedButtonSetstatuscallback()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    int iRet = VLPR_SetStatusCallBack(m_iIndex, 10, CBFun_GetDevStatus, this);
    char chLog[MAX_PATH] = { 0 };
    sprintf_s(chLog, "VLPR_SetStatusCallBack , nHandle = %d, ����ֵΪ %d", m_iIndex, iRet);
    MessageBox(chLog);
}


void CTestVPR_HLJDlg::OnBnClickedButtonManualsnap()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    int iRet = VLPR_ManualSnap(m_iIndex);
    char chLog[MAX_PATH] = { 0 };
    sprintf_s(chLog, "VLPR_ManualSnap , nHandle = %d, ����ֵΪ %d", m_iIndex, iRet);
    MessageBox(chLog);
}


void CTestVPR_HLJDlg::OnBnClickedButtonGetstatus()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    int  piStatusCode;
    int iRet = VLPR_GetStatus(m_iIndex, &piStatusCode);
    char chLog[MAX_PATH] = { 0 };
    sprintf_s(chLog, "VLPR_ManualSnap , nHandle = %d, Statusdode = %d, ����ֵΪ %d", m_iIndex, piStatusCode, iRet);
    MessageBox(chLog);
}


void CTestVPR_HLJDlg::OnBnClickedButtonGetstatusmsg()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    int nStatusCode = 0;
    CString strCode;
    GetDlgItem(IDC_EDIT_Code)->GetWindowText(strCode);
    if (strCode.IsEmpty())
    {
        nStatusCode = 0;
    }
    else
    {
        nStatusCode = atoi(strCode.GetBuffer());
        strCode.ReleaseBuffer();
    }
    
    char chStatusMsg[MAX_PATH] = {0};
    int nStatusMsgLen = sizeof(chStatusMsg);
    int iRet = VLPR_GetStatusMsg(nStatusCode, chStatusMsg, nStatusMsgLen);

    char chLog[MAX_PATH] = { 0 };
    sprintf_s(chLog, "VLPR_ManualSnap , nStatusCode = %d, chStatusMsg = %s, nStatusMsgLen = %d, ����ֵΪ %d", nStatusCode, chStatusMsg, nStatusMsgLen, iRet);
    MessageBox(chLog);
}


void CTestVPR_HLJDlg::OnBnClickedButtonGetversion()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    char chVersionInfo[MAX_PATH] = { 0 };
    int iVrLength = sizeof(chVersionInfo);
    int iRet = VLPR_GetVersion(chVersionInfo, iVrLength);

    char chLog[MAX_PATH] = { 0 };
    sprintf_s(chLog, "VLPR_GetVersion , chVersionInfo = %s, iVrLength = %d, ����ֵΪ %d", chVersionInfo, iVrLength, iRet);
    MessageBox(chLog);
}

void CTestVPR_HLJDlg::SaveVPRResult(T_VLPINFO *vlpInfo)
{
    char szVehPlate[128];
    memcpy(szVehPlate, vlpInfo->vlpText, sizeof(vlpInfo->vlpText));

    char chSaveText[1024] = {0};
    sprintf_s(chSaveText, "���ƺţ�%s\r\n���Ŷ�:%d\r\n��ɫ��%s\r\nʱ�䣺%s\r\n��ͼ���ȣ�%d\r\nСͼ����:%d\r\n��ֵͼ���ȣ�%d\r\n",
        vlpInfo->vlpText,
        vlpInfo->vlpReliability,
        vlpInfo->vlpColor,
        vlpInfo->vlpTime,
        vlpInfo->imageLength[0],
        vlpInfo->imageLength[1],
        vlpInfo->imageLength[2]);


    //[0]=����ͼ���ȣ�[1]=����ͼ���ȣ�[2]=��ֵ��ͼ����

    TCHAR szFilePath[MAX_PATH] = { 0 };
    char chFileName[MAX_PATH] = { 0 };

    GetModuleFileName(NULL, szFilePath, MAX_PATH);	//ȡ�ð�����������ȫ·��
    PathRemoveFileSpec(szFilePath);				//ȥ��������

    char chPath[MAX_PATH] = {0};
    sprintf_s(chPath, "%s\\result\\", szFilePath);
    MakeSureDirectoryPathExists(chPath);
    
    sprintf_s(chFileName, "%s\\%s_%s_Big.jpg", chPath, vlpInfo->vlpTime, vlpInfo->vlpText);
    //std::string fileName = std::string(".\\result\\") + vlpInfo->vlpTime + std::string("_") + vlpInfo->vlpText + "Big.jpg";
    if (WriteBufToFile(chFileName, vlpInfo->image[0], vlpInfo->imageLength[0]));

    memset(chFileName, '\0', sizeof(chFileName));
    sprintf_s(chFileName, "%s\\%s_%s_Small.jpg", chPath,vlpInfo->vlpTime, vlpInfo->vlpText);
    //fileName = std::string(".\\result\\") + vlpInfo->vlpTime + "Small.jpg";
    if (WriteBufToFile(chFileName, vlpInfo->image[1], vlpInfo->imageLength[1]));

    memset(chFileName, '\0', sizeof(chFileName));
    sprintf_s(chFileName, "%s\\%s_%s_Bin.jpg", chPath, vlpInfo->vlpTime, vlpInfo->vlpText);
    //fileName = std::string(".\\result\\") + vlpInfo->vlpTime + "Bin.jpg";
    if (WriteBufToFile(chFileName, vlpInfo->image[2], vlpInfo->imageLength[2]));

    memset(chFileName, '\0', sizeof(chFileName));
    sprintf_s(chFileName, "%s\\%s_%s_Inf.txt", chPath, vlpInfo->vlpTime, vlpInfo->vlpText);
    FILE* pFile = NULL;
    //file = fopen(chLogFileName, "a+");
    fopen_s(&pFile, chFileName, "a+");
    if (pFile)
    {
        fwrite(chSaveText, 1, sizeof(chSaveText), pFile);
        fclose(pFile);
        pFile = NULL;
    }

    GetDlgItem(IDC_EDIT_showPlate)->SetWindowTextA(chSaveText);
}

BOOL CTestVPR_HLJDlg::WriteBufToFile(LPCTSTR lpImageName, const LPBYTE lpBuffer, UINT nBufferLen)
{
    HANDLE hFileHandle = CreateFile(
        lpImageName,
        GENERIC_WRITE,
        FILE_SHARE_READ,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        0);
    if (INVALID_HANDLE_VALUE == hFileHandle)
    {
        return FALSE;
    }
    DWORD dwBytesWritten = 0;
    if (!WriteFile(hFileHandle, lpBuffer, nBufferLen, &dwBytesWritten, NULL))
    {
        CloseHandle(hFileHandle);
        return FALSE;
    }
    CloseHandle(hFileHandle);
    return (dwBytesWritten == nBufferLen);
}

void CTestVPR_HLJDlg::CBFun_GetDevStatus(int nHandle, int nStatus, void* pUser)
{
    if (pUser)
    {
        CTestVPR_HLJDlg* pDlg = (CTestVPR_HLJDlg*)pUser;
        CString cstrLog;
        if (nStatus == 0)
        {
            cstrLog.Format("������״̬��Ϊ %d", nStatus);
        }
        else
        {
            cstrLog.Format("�쳣��״̬��Ϊ %d", nStatus);
        }
        pDlg->GetDlgItem(IDC_STATIC_Status)->SetWindowTextA(cstrLog);
    }
}

void CTestVPR_HLJDlg::CBFun_GetRegResult(int nHandle, T_VLPINFO* pVlpResult, void *pUser)
{
    if (pUser)
    {
        CTestVPR_HLJDlg* pDlg = (CTestVPR_HLJDlg*)pUser;
        pDlg->SaveVPRResult(pVlpResult);
    }
}
