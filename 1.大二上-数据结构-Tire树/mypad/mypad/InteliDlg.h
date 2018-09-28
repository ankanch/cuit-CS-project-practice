#pragma once
#include "afxwin.h"
#include "TrieTree.h"


// CInteliDlg 对话框

class CInteliDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInteliDlg)

public:
	CInteliDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CInteliDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INTEL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_intellist;
	void SetWORDData(WORDSTACK &ws);
};
