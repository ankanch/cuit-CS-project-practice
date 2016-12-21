// SearchSuggestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mypad.h"
#include "SearchSuggestDlg.h"
#include "afxdialogex.h"


// CSearchSuggestDlg 对话框

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


// CSearchSuggestDlg 消息处理程序


void CSearchSuggestDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString data = "";
	m_searchword.GetWindowTextA(data);
	trie->Suggest(data, "", ws, trie->GetRoot());
	int i = 0;
	m_searchresultlist.DeleteAllItems();
	CString pp;
	pp.Format("共 %d 个结果",ws.size());
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

	// TODO:  在此添加额外的初始化
	m_searchresultlist.InsertColumn(0,"单词" ,LVCFMT_CENTER, 140);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
