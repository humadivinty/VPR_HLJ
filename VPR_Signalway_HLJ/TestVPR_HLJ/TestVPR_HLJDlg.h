
// TestVPR_HLJDlg.h : ͷ�ļ�
//

#pragma once
#include "../VPR_Signalway_HLJ/CommonDef_VPR.h"


// CTestVPR_HLJDlg �Ի���
class CTestVPR_HLJDlg : public CDialogEx
{
// ����
public:
	CTestVPR_HLJDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TESTVPR_HLJ_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButtonInit();
    afx_msg void OnBnClickedButtonLogin();
    afx_msg void OnBnClickedButtonLogout();
    afx_msg void OnBnClickedButtonDeinit();
    afx_msg void OnBnClickedButtonSetresultcallback();
    afx_msg void OnBnClickedButtonSetstatuscallback();
    afx_msg void OnBnClickedButtonManualsnap();
    afx_msg void OnBnClickedButtonGetstatus();
    afx_msg void OnBnClickedButtonGetstatusmsg();
    afx_msg void OnBnClickedButtonGetversion();

private:
    int m_iIndex;

    void SaveVPRResult(T_VLPINFO *vlpInfo);
    BOOL WriteBufToFile(LPCTSTR lpImageName, const LPBYTE lpBuffer, UINT nBufferLen);
public:
    
   static void CBFun_GetDevStatus(int nHandle, int nStatus, void* pUser);

   static void CBFun_GetRegResult(int nHandle, T_VLPINFO* pVlpResult, void *pUser);


};
