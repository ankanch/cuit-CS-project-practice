// NewLineDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MetroLookup_LineDrawer.h"
#include "MetroLookup_LineDrawerDlg.h"
#include "NewLineDlg.h"
#include "afxdialogex.h"


// CNewLineDlg �Ի���

IMPLEMENT_DYNAMIC(CNewLineDlg, CDialogEx)

CNewLineDlg::CNewLineDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CNewLineDlg::~CNewLineDlg()
{
}

void CNewLineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, m_clolor_new_line);
}


BEGIN_MESSAGE_MAP(CNewLineDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CNewLineDlg::OnBnClickedOk)
	ON_EN_SETFOCUS(IDC_EDIT_NEW_LINE_BEG_STATION, &CNewLineDlg::OnEnSetfocusEditNewLineBegStation)
	ON_EN_SETFOCUS(IDC_EDIT_NEW_LINE_END_STATION, &CNewLineDlg::OnEnSetfocusEditNewLineEndStation)
	ON_EN_SETFOCUS(IDC_EDIT_NEW_LINE_PRICE, &CNewLineDlg::OnEnSetfocusEditNewLinePrice)
	ON_EN_KILLFOCUS(IDC_EDIT_NEW_LINE_BEG_STATION, &CNewLineDlg::OnEnKillfocusEditNewLineBegStation)
	ON_EN_KILLFOCUS(IDC_EDIT_NEW_LINE_END_STATION, &CNewLineDlg::OnEnKillfocusEditNewLineEndStation)
	ON_EN_KILLFOCUS(IDC_EDIT_NEW_LINE_PRICE, &CNewLineDlg::OnEnKillfocusEditNewLinePrice)
END_MESSAGE_MAP()


// CNewLineDlg ��Ϣ�������


void CNewLineDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString fbuf,snbbuf,snebuf,pbuf;
	GetDlgItemTextW(IDC_EDIT_NEW_LINE_BEG_STATION, snbbuf);
	GetDlgItemTextW(IDC_EDIT_NEW_LINE_END_STATION, snebuf);
	GetDlgItemTextW(IDC_EDIT_NEW_LINE_PRICE, pbuf);
	
	if (  snbbuf.IsEmpty() || snebuf.IsEmpty() || pbuf.IsEmpty() 
		 || snbbuf == STR_STABEG || snebuf == STR_STAEND || pbuf == STR_PRICE)
	{
		MessageBox(_T("����������Ч"), _T("����"), MB_ICONERROR | MB_OK);
	}
	else
	{
		int ibuf;
		ibuf = _ttoi(pbuf);
		CMLLDDlg *mlldlg = (CMLLDDlg*)GetParent();
		mlldlg->SetStaBegName(snbbuf);
		mlldlg->SetStaEndName(snebuf);
		mlldlg->SetTermPrice(ibuf);
		//�����ɫ
		COLORREF clr = m_clolor_new_line.GetColor();
		mlldlg->SetLineColor(clr);

		CDialogEx::OnOK();
	}
}


BOOL CNewLineDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GetDlgItem(IDC_EDIT_NEW_LINE_BEG_STATION)->SetWindowTextW(STR_STABEG);
	GetDlgItem(IDC_EDIT_NEW_LINE_END_STATION)->SetWindowTextW(STR_STAEND);
	GetDlgItem(IDC_EDIT_NEW_LINE_PRICE)->SetWindowTextW(STR_PRICE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}



void CNewLineDlg::OnEnSetfocusEditNewLineBegStation()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString buf;
	GetDlgItem(IDC_EDIT_NEW_LINE_BEG_STATION)->GetWindowTextW(buf);
	if (buf == STR_STABEG)
	{
		GetDlgItem(IDC_EDIT_NEW_LINE_BEG_STATION)->SetWindowTextW(_T(""));
	}
}


void CNewLineDlg::OnEnSetfocusEditNewLineEndStation()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString buf;
	GetDlgItem(IDC_EDIT_NEW_LINE_END_STATION)->GetWindowTextW(buf);
	if (buf == STR_STAEND)
	{
		GetDlgItem(IDC_EDIT_NEW_LINE_END_STATION)->SetWindowTextW(_T(""));
	}
}


void CNewLineDlg::OnEnSetfocusEditNewLinePrice()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString buf;
	GetDlgItem(IDC_EDIT_NEW_LINE_PRICE)->GetWindowTextW(buf);
	if (buf == STR_PRICE)
	{
		GetDlgItem(IDC_EDIT_NEW_LINE_PRICE)->SetWindowTextW(_T(""));
	}
}


void CNewLineDlg::OnEnKillfocusEditNewLineBegStation()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString buf;
	GetDlgItem(IDC_EDIT_NEW_LINE_BEG_STATION)->GetWindowTextW(buf);
	if (buf == _T("") || buf == _T(" "))
	{
		GetDlgItem(IDC_EDIT_NEW_LINE_BEG_STATION)->SetWindowTextW(STR_STABEG);
	}
}


void CNewLineDlg::OnEnKillfocusEditNewLineEndStation()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString buf;
	GetDlgItem(IDC_EDIT_NEW_LINE_END_STATION)->GetWindowTextW(buf);
	if (buf == _T("") || buf == _T(" "))
	{
		GetDlgItem(IDC_EDIT_NEW_LINE_END_STATION)->SetWindowTextW(STR_STAEND);
	}
}


void CNewLineDlg::OnEnKillfocusEditNewLinePrice()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString buf;
	GetDlgItem(IDC_EDIT_NEW_LINE_PRICE)->GetWindowTextW(buf);
	if (buf == _T("") || buf == _T(" "))
	{
		GetDlgItem(IDC_EDIT_NEW_LINE_PRICE)->SetWindowTextW(STR_PRICE);
	}
}
