// SetPresentionSpeed.cpp : 实现文件
//

#include "stdafx.h"
#include "mypad.h"
#include "SetPresentionSpeed.h"
#include "afxdialogex.h"


// CSetPresentionSpeed 对话框

IMPLEMENT_DYNAMIC(CSetPresentionSpeed, CDialogEx)

CSetPresentionSpeed::CSetPresentionSpeed(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_SET_SHOW_MILLSECOND, pParent)
{

}

CSetPresentionSpeed::~CSetPresentionSpeed()
{
}

void CSetPresentionSpeed::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetPresentionSpeed, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSetPresentionSpeed::OnBnClickedOk)
END_MESSAGE_MAP()


// CSetPresentionSpeed 消息处理程序


BOOL CSetPresentionSpeed::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	buf.Format("%d", tg->getPresentionMilesecond());
	SetDlgItemText(IDC_EDIT_SHOW_MILESECOND, buf);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CSetPresentionSpeed::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItemText(IDC_EDIT_SHOW_MILESECOND, buf);
	tg->setPresentionMilesecond(_ttoi(buf));
	CDialogEx::OnOK();
}
