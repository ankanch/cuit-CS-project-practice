// SetPresentionSpeed.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mypad.h"
#include "SetPresentionSpeed.h"
#include "afxdialogex.h"


// CSetPresentionSpeed �Ի���

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


// CSetPresentionSpeed ��Ϣ�������


BOOL CSetPresentionSpeed::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	buf.Format("%d", tg->getPresentionMilesecond());
	SetDlgItemText(IDC_EDIT_SHOW_MILESECOND, buf);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CSetPresentionSpeed::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItemText(IDC_EDIT_SHOW_MILESECOND, buf);
	tg->setPresentionMilesecond(_ttoi(buf));
	CDialogEx::OnOK();
}
