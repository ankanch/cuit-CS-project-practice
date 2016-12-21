// SearchSuggestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mypad.h"
#include "SearchSuggestDlg.h"
#include "afxdialogex.h"


// CSearchSuggestDlg �Ի���

IMPLEMENT_DYNAMIC(CSearchSuggestDlg, CDialogEx)

CSearchSuggestDlg::CSearchSuggestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_SUGGESTDIALOG, pParent)
{

}

CSearchSuggestDlg::~CSearchSuggestDlg()
{
	if (trie != nullptr)
	{
		delete trie;
	}
}

void CSearchSuggestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_searchword);
	DDX_Control(pDX, IDC_LIST_POSSIBLE_WORDS, m_searchresultlist);
	DDX_Control(pDX, IDC_STATIC_SUGGEST_TIPS, m_tips);
}


BEGIN_MESSAGE_MAP(CSearchSuggestDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &CSearchSuggestDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CSearchSuggestDlg ��Ϣ�������


void CSearchSuggestDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString data = "";
	m_searchword.GetWindowTextA(data);
	trie->Suggest(data, "", ws, trie->GetRoot());
	int i = 0;
	m_searchresultlist.DeleteAllItems();
	CString pp;
	pp.Format("�� %d �����",ws.size());
	m_tips.SetWindowTextA(pp);
	while (!ws.empty())
	{
		m_searchresultlist.InsertItem(i, "");
		m_searchresultlist.SetItemText(i, 0, data+ws.top());
		i++;
		ws.pop();
	}

}


BOOL CSearchSuggestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_searchresultlist.InsertColumn(0,"����" ,LVCFMT_CENTER, 140);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
