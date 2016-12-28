
// mypadDlg.h : header file
//

#pragma once
#include "TrieTree.h"
#include "TrieGraph.h"
#include "InteliDlg.h"
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
	const WORDSTACK  RetriveWords(const CString raw);	//����һ�����飬���������е��ʣ����һ��������"\0"��β�������Կո�ָ�
	CTrieTree triedata;
public:
	// ���༭��
	CEdit m_edit;
	//����
	CFont * f;
	//����༭���ڿո���֮ǰ�����ݣ�������������Trie��
	CString last_edit_data;
	//����Ƿ���Ҫ����Trie
	bool ins_avb;
	//���ɾ��������
	bool del_pressed;
	//VK_DOWN 
	bool clkvkdown;
	//��¼��һ������ĵ���
	CString lastword;
	//��¼��һ�ΰ��¿ո�ʱ�����λ��
	int last_sel_pos;
	//����Trie���ĶԻ���ָ��
	CTrieGraph *triegraphdlg;
	//������ʾ�Ի���ָ��
	CInteliDlg *intdlg;
	CListBox *lb;
	//���������ʾ��״̬
	bool INK;

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnMenuShowTrie();
	afx_msg void OnMenuTf();
	afx_msg void OnMenuSort();
	afx_msg void OnMenuSearch();
	CStatic m_tipsxx;
};
