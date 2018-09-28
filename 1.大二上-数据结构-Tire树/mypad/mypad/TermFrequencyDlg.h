#pragma once
#include "afxcmn.h"
#include "TrieTree.h"
#include "afxwin.h"


// CTermFrequencyDlg �Ի���

class CTermFrequencyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTermFrequencyDlg)

public:
	CTermFrequencyDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTermFrequencyDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TERMFREQUENCY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
