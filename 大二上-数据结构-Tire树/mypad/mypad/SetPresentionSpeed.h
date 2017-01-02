#pragma once
#include "mypadDlg.h"
#include "TrieGraph.h"

// CSetPresentionSpeed �Ի���

class CSetPresentionSpeed : public CDialogEx
{
	DECLARE_DYNAMIC(CSetPresentionSpeed)

public:
	CSetPresentionSpeed(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetPresentionSpeed();
	void setTrieGraphDlg( CTrieGraph * pdlg) { tg = pdlg; }

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SET_SHOW_MILLSECOND };
#endif
private:
	CTrieGraph *tg;
	CString buf;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
