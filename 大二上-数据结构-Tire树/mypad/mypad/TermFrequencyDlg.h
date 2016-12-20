#pragma once
#include "afxcmn.h"
#include "TrieTree.h"
#include "afxwin.h"


// CTermFrequencyDlg 对话框

class CTermFrequencyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTermFrequencyDlg)

public:
	CTermFrequencyDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTermFrequencyDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TERMFREQUENCY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CString rawdata;
	CTrieTree *pt;
public:
	CListCtrl m_tflist;
	virtual BOOL OnInitDialog();
	void setTrie(CTrieTree *tt);
	void setRaw(CString raw);
	CStatic m_tipsx;
};
