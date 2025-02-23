// InteliDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mypad.h"
#include "InteliDlg.h"
#include "afxdialogex.h"


// CInteliDlg 对话框

IMPLEMENT_DYNAMIC(CInteliDlg, CDialogEx)

CInteliDlg::CInteliDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_INTEL, pParent)
{

}

CInteliDlg::~CInteliDlg()
{
}

void CInteliDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_INTEL, m_intellist);
}

void CInteliDlg::SetWORDData(WORDSTACK & ws)
{
	m_intellist.ResetContent();
	while (!ws.empty())
	{
		m_intellist.AddString( ws.top());
		ws.pop();
	}
}


BEGIN_MESSAGE_MAP(CInteliDlg, CDialogEx)
END_MESSAGE_MAP()


// CInteliDlg 消息处理程序
