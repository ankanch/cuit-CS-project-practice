// TermFrequencyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mypad.h"
#include "TermFrequencyDlg.h"
#include "afxdialogex.h"


// CTermFrequencyDlg �Ի���

IMPLEMENT_DYNAMIC(CTermFrequencyDlg, CDialogEx)

CTermFrequencyDlg::CTermFrequencyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_TERMFREQUENCY, pParent)
{

}

CTermFrequencyDlg::~CTermFrequencyDlg()
{
}

void CTermFrequencyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_TERMFREQUENCY, m_tflist);
	DDX_Control(pDX, IDC_STATIC_TIPS, m_tipsx);
}


BEGIN_MESSAGE_MAP(CTermFrequencyDlg, CDialogEx)
END_MESSAGE_MAP()


// CTermFrequencyDlg ��Ϣ�������


BOOL CTermFrequencyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_tflist.InsertColumn(0, "����",LVCFMT_CENTER, 140);
	m_tflist.InsertColumn(1, "Ƶ��", LVCFMT_CENTER, 60);

	CString buf;
	TFDLIST tl = pt->GetTermFrequencyList();
	for (int i = 0; i < tl.size(); i++)
	{
		TFD tfd = tl.at(i);
		buf.Format("%s,%d\n", tfd.first, tfd.second);
		m_tflist.InsertItem(i,buf.Mid(2));
		buf.Format("%d", tfd.second);
		m_tflist.SetItemText(i, 0, tfd.first.Mid(2));
		m_tflist.SetItemText(i, 1, buf);
	}
	CString pp;
	pp.Format("�� %d �����ʣ��������Ϊ %d ��Ƶ����ߵ�Ϊ %s", tl.size(), 0, "NULL");
	m_tipsx.SetWindowTextA(pp);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

void CTermFrequencyDlg::setTrie(CTrieTree * tt)
{
	pt = tt;
}

void CTermFrequencyDlg::setRaw(CString raw)
{
	rawdata = raw;
}
