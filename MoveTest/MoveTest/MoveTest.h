
// MoveTest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMoveTestApp: 
// �йش����ʵ�֣������ MoveTest.cpp
//

class CMoveTestApp : public CWinApp
{
public:
	CMoveTestApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMoveTestApp theApp;