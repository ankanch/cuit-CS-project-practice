
// mypadDlg.h : header file
//

#pragma once
#include "TrieTree.h"
#include "afxwin.h"

class CmypadDlgAutoProxy;


// CMypadDlg dialog
class CMypadDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMypadDlg);
	friend class CmypadDlgAutoProxy;

// Construction
public:
	CMypadDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CMypadDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYPAD_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	CmypadDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditContent();
private:
	CTrieTree triedata;
public:
	// Ö÷±à¼­¿ò
	CEdit m_edit;
	//×ÖÌå
	CFont * f;
};
