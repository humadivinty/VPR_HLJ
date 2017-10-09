
// TestVPR_HLJDlg.h : 头文件
//

#pragma once
#include "../VPR_Signalway_HLJ/CommonDef_VPR.h"


// CTestVPR_HLJDlg 对话框
class CTestVPR_HLJDlg : public CDialogEx
{
// 构造
public:
	CTestVPR_HLJDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TESTVPR_HLJ_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
