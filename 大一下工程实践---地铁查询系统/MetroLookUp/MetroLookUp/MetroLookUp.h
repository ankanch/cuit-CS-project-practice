
// MetroLookUp.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMLIApp: 
// �йش����ʵ�֣������ MetroLookUp.cpp
//

class CMLIApp : public CWinApp
{
public:
	CMLIApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMLIApp theApp;