#pragma once
#include "afxwin.h"
#include "TrieTree.h"


// CInteliDlg �Ի���

class CInteliDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInteliDlg)

public:
	CInteliDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInteliDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INTEL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_intellist;
	void SetWORDData(WORDSTACK &ws);
};
