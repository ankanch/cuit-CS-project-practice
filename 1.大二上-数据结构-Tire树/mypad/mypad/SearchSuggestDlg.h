#pragma once
#include "TrieTree.h"
#include "mypadDlg.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "TrieGraph.h"

// CSearchSuggestDlg �Ի���

class CSearchSuggestDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSearchSuggestDlg)

public:
	CSearchSuggestDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSearchSuggestDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SUGGESTDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CMypadDlg mypaddlg;
	CTrieGraph *tg;
	CTrieTree *trie;
	WORDSTACK ws;
public:
	afx_msg void OnEnChangeEdit1();
	CEdit m_searchword;
	CListCtrl m_searchresultlist;
	void SetTrieData(CTrieTree *triedata) { trie = triedata; }
	void SetTrieGraphDlg(CTrieGraph *triegraph) { tg = triegraph; }
	virtual BOOL OnInitDialog();
	CStatic m_tips;
};
