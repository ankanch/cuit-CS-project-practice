
// MetroLookup_LineDrawer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMLLDApp: 
// �йش����ʵ�֣������ MetroLookup_LineDrawer.cpp
//

class CMLLDApp : public CWinApp
{
public:
	CMLLDApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMLLDApp theApp;