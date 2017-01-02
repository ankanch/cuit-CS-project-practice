#pragma once
#include "mypadDlg.h"
#include "TrieGraph.h"

// CSetPresentionSpeed 对话框

class CSetPresentionSpeed : public CDialogEx
{
	DECLARE_DYNAMIC(CSetPresentionSpeed)

public:
	CSetPresentionSpeed(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetPresentionSpeed();
	void setTrieGraphDlg( CTrieGraph * pdlg) { tg = pdlg; }

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SET_SHOW_MILLSECOND };
#endif
private:
	CTrieGraph *tg;
	CString buf;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
