#pragma once
#include "TrieTree.h"
#include "mypadDlg.h"
#include "afxwin.h"
#include "afxcmn.h"

// CSearchSuggestDlg 对话框

class CSearchSuggestDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSearchSuggestDlg)

public:
	CSearchSuggestDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSearchSuggestDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SUGGESTDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CMypadDlg mypaddlg;
	CTrieTree *trie;
	WORDSTACK ws;
public:
	afx_msg void OnEnChangeEdit1();
	CEdit m_searchword;
	CListCtrl m_searchresultlist;
	void SetTrieData(CTrieTree *triedata) { trie = triedata; }
	virtual BOOL OnInitDialog();
	CStatic m_tips;
};
