
// LSBInfoHide.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CLSBInfoHideApp: 
// �йش����ʵ�֣������ LSBInfoHide.cpp
//

class CLSBInfoHideApp : public CWinApp
{
public:
	CLSBInfoHideApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CLSBInfoHideApp theApp;
