
// mypadDlg.h : header file
//

#pragma once
#include "TrieTree.h"
#include "TrieGraph.h"
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
	// 主编辑框
	CEdit m_edit;
	//字体
	CFont * f;
	//储存编辑框在空格按下之前的数据，用于增量创建Trie树
	CString last_edit_data;
	//标记是否需要插入Trie
	bool ins_avb;
	//记录上一次按下空格时候光标的位置
	int last_sel_pos;
	//绘制Trie树的对话框指针
	CTrieGraph *triegraphdlg;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnMenuShowTrie();
};
