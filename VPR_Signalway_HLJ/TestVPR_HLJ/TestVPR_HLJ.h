
// TestVPR_HLJ.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTestVPR_HLJApp: 
// �йش����ʵ�֣������ TestVPR_HLJ.cpp
//

class CTestVPR_HLJApp : public CWinApp
{
public:
	CTestVPR_HLJApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTestVPR_HLJApp theApp;